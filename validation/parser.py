#!/usr/bin/env python

# hadrontherapy portal parser: metadata() reads the macro, parse() the
# RBE-accumulated AlphaAndBeta.out (radiobiological alpha/beta for the
# depth-214 voxel slice) into a modelled cell-survival curve.
#
# Ported from geant-config-generator/tests/geant4/hadrontherapy/parser.py
# (gts.BaseParser, which shelled out to run analysis_geantval.py as a
# subprocess) to the module-level metadata()/parse() API expected by
# ci-workflows/validation/export.py. The survival-curve computation from
# analysis_geantval.py is inlined directly (no subprocess, no numpy
# dependency, no experimental-reference overlay — the original invocation
# never passed a reference file as argv[1] either, so only the modelled
# curve was ever produced in practice).
import math
import os

from geantval import getJSON, one_command, single_run

DEPTH_SLICE = 214  # voxel index in AlphaAndBeta.out this test reports on


def metadata(commands):
    single_run(commands)
    energy, unit = one_command(commands, "/gps/ene/mono").split()
    if unit != "MeV":
        raise ValueError("Expected a MeV beam energy, got: " + unit)
    return {"TEST": "hadrontherapy",
            "PHYSICS_LIST": one_command(commands, "/Physics/addPhysics"),
            "PARTICLE": one_command(commands, "/gps/particle"),
            "ENERGY": float(energy),
            "DETECTOR": one_command(commands, "/rbe/cellLine")}


def read_alpha_beta(filename, depth_slice):
    with open(filename) as f:
        next(f)  # header: "alpha  beta  depth(slice)"
        for line in f:
            a, b, d = line.split()
            if int(d) == depth_slice:
                return float(a), float(b)
    raise ValueError("No depth-slice %d row found in %s" % (depth_slice, filename))


def parse(job):
    alpha, beta = read_alpha_beta(os.path.join(job["path"], "AlphaAndBeta.out"), DEPTH_SLICE)

    doseData = [i * 5. / 9. for i in range(10)]  # Gy, matches numpy.linspace(0, 5, num=10)
    survival = [math.exp(-alpha * d - beta * d * d) for d in doseData]

    rjson = getJSON(job, "chart",
                     mctool_name="GEANT4",
                     mctool_model=job["PHYSICS_LIST"],
                     observableName="survival fraction",
                     targetName=job["DETECTOR"],
                     beamParticle=job["PARTICLE"],
                     beamEnergies=[job["ENERGY"]],
                     title="survival fraction",
                     xAxisName="Dose, Gy",
                     yAxisName="Survival Fraction",
                     xValues=doseData,
                     yValues=survival)
    yield rjson

# Portal JSON parser

Rewritten from `geant-config-generator/tests/geant4/hadrontherapy/parser.py`
(old `gts.BaseParser`, which shelled out to run `analysis_geantval.py` as a
subprocess inside the job directory) for the module-level
`metadata()`/`parse()` API that `ci-workflows/validation/export.py` actually
calls. `analysis_geantval.py`'s survival-curve computation is inlined
directly (plain Python, no `numpy`, no subprocess) — the original invocation
never passed an experimental reference file as `sys.argv[1]` either, so in
practice only the modelled curve (`doseData = numpy.linspace(0, 5, num=10)`,
`survival = exp(-alpha*dose - beta*dose**2)`) was ever produced; that part is
reproduced exactly (including the depth-214-voxel alpha/beta lookup from
`AlphaAndBeta.out`).

## The macro: not self-contained in its original form, and why

`batch.mac` (the only macro `geant-validation-tests/src/hadrontherapy`
itself ships) sets **no** `/rbe/...` commands at all, so
`HadrontherapyRBE::StoreAlphaAndBeta()` — gated by
`rbe->IsCalculationEnabled()` — would never fire and `AlphaAndBeta.out` would
never be written. The real, working configuration lives in
`geant-config-generator/tests/geant4/hadrontherapy/template.conf`, which:

- loads an RBE LEM table (`/rbe/loadLemTable data/rbe/lem3_MDA.csv`) and
  selects cell line `MDA` (`/rbe/cellLine MDA`), both copied into
  `macro/data/rbe/` and `macro/Modulators/` here (the modulator wheel data
  files, read via `/modulator/ReadData`'s default filename, come from
  `geant-validation-tests/src/hadrontherapy/Modulators/`);
- drives a rotating-wheel range modulator through
  `/control/loop macro/modulator.loop counterName 0 359 1`, 360 iterations
  of `/modulator/angle 1 deg` + `/run/beamOn 1000` — which `read_macro()`
  rejects (`/control/loop`, `/control/alias`, unresolved `{counterName}`).

`modulator.loop`'s body sets the angle to the **same literal `1 deg` on
every iteration** (it never actually substitutes the loop counter into
`/modulator/angle`), so the 360 iterations are 360 statistically independent
runs of the *same* fixed geometry, RBE-accumulated (`/rbe/accumulate 1`)
into one running total — physically identical to one run of
`beamOn 360000` at that same fixed angle. `macro/HADRONTHERAPY_2_62MeV_MDA.mac`
replaces the loop with exactly that single, self-contained `beamOn 360000`,
keeping the rest of the real `template.conf` (RBE/modulator setup, 62.4 MeV
proton beam, `HADRONTHERAPY_2` physics list) unchanged. The other two
`params.conf` physics lists (`HADRONTHERAPY_1`, `standard_opt4`) are not
included — generate more macros the same way if needed.

The RBE/modulator data file **relative paths** this macro expects
(`data/rbe/lem3_MDA.csv`, the default `ModulWeight.txt`-style modulator
file) assume the working directory layout `geant-config-generator` itself
uses; wiring this into `ci-workflows` may need the run's working directory
adjusted so `macro/data/` and `macro/Modulators/` resolve the same way.

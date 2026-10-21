# hadrontherapy

**62 MeV proton beam test: cell survival modelling and averaged LET track**,
based on the Geant4 advanced example `hadrontherapy` (INFN, MC-INFN group).
Last text-README revision: F. Romano, Nov. 2015 (Geant4 10.2).

---

## 🔬 What this test does

A 62 MeV proton pencil beam (`/gps/ene/mono 62 MeV`, `macro/batch.mac`) is
delivered to a phantom; the simulation scores the dose and the
track-averaged LET (linear energy transfer), used downstream for radiobiological
cell-survival modelling (`analysis_geantval.py`).

## 📚 Reference

- Source: `geant-validation-tests/src/hadrontherapy` (Geant4 advanced
  example `hadrontherapy`, INFN/MC-INFN group).
- See the full documentation at the Hadrontherapy TWiki page referenced in
  the original README.

## Import notes

- `main.cc`, `include/`, `src/` come from `hadrontherapy.cc`/`include`/`src`.
- `macro/` contains `batch.mac`, the only macro found directly in
  `geant-validation-tests/src/hadrontherapy` (kept for reference, not used
  by CI — it doesn't configure RBE at all, see below), plus one concrete,
  self-contained macro (`HADRONTHERAPY_2_62MeV_MDA.mac`) built from
  `geant-config-generator`'s real, working `template.conf`, with its
  360-iteration `/control/loop` modulator sweep flattened into one
  equivalent `beamOn`, and its required RBE/modulator data files copied
  alongside under `macro/data/` and `macro/Modulators/` — see
  `validation/README.md` for the full reasoning.
- `validation/parser.py` was **rewritten** for the `metadata()`/`parse()`
  module API that `ci-workflows/validation/export.py` actually calls (the
  first version, copied unmodified from
  `geant-config-generator/tests/geant4/hadrontherapy/parser.py`, used the
  old `gts.BaseParser` class API — and shelled out to run
  `analysis_geantval.py` as a subprocess, now inlined directly instead).
  See `validation/README.md` for details. The vendored `gts` package is no
  longer needed and was removed.
- A related but distinct test, `heavy_ion_therapy` (carbon/oxygen ion beams,
  148.5-350 MeV/u, BIC/QMD/INCL models), was ruled out for this slide item —
  it uses heavy ions, not 62 MeV protons.

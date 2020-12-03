{ pkgs }:

with pkgs;
let
  cfg = writeTextFile {
    name = "mpi.cfg";
    text = (
      lib.generators.toINI
        { }
        {
          mpi = {
            mpicc = "${openmpi.outPath}/bin/mpicc";
          };
        }
    );
  };
in
poetry2nix.mkPoetryEnv {
  python = python3;
  projectDir = ./..;
  overrides = poetry2nix.overrides.withDefaults (self: super: {
    mpi4py = super.mpi4py.overridePythonAttrs (
      old: {
        preBuild = ''
          ln -sf ${cfg} mpi.cfg
        '';
        propagatedBuildInputs = old.propagatedBuildInputs ++ [ openmpi ];
      }
    );
    sphinx-rtd-theme = super.sphinx_rtd_theme;
  });
}

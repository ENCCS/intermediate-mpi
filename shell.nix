let
  sources = import ./nix/sources.nix;
  pkgs = import sources.nixpkgs {
    overlays = [
      (self: super: { })
      (import (sources.poetry2nix + "/overlay.nix"))
    ];
  };
  pythonEnv = import ./nix/pythonEnv.nix { inherit pkgs; };
in
pkgs.mkShell {
  name = "intermediate-mpi";
  nativeBuildInputs = with pkgs; [
    clang-tools
    cmake
    gcc
    ninja
    openmpi
    pythonEnv
  ];
  buildInputs = with pkgs; [
    gdb
    valgrind
  ];
  hardeningDisable = [ "all" ];
  NINJA_STATUS = "[Built edge %f of %t in %e sec] ";
}

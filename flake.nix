{
  description = "intermediate-mpi";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    mach-nix.url = "github:DavHau/mach-nix/3.4.0";
  };

  outputs = { self, nixpkgs, flake-utils, mach-nix }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        pythonEnv = mach-nix.lib."${system}".mkPython {
          requirements = builtins.readFile ./requirements.txt;
        };
      in
      {
        devShell = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            clang-tools
            cmake
            gcc
            ninja
            openmpi
            pythonEnv
          ];

          hardeningDisable = [ "all" ];

          NINJA_STATUS = "[Built edge %f of %t in %e sec] ";
        };
      });
}

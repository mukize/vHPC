{
  stdenv,
  raylib,
}:
stdenv.mkDerivation {
  name = "vhpc";
  version = "0.1.0";
  src = ./.;
  buildInputs = [
    raylib
  ];

  installFlags = [ "PREFIX=${placeholder "out"}" ];

}

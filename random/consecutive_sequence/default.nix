{ system ? builtins.currentSystem, doCheck ? true }:

with import <nixpkgs> { inherit system; };

stdenv.mkDerivation rec {
   inherit doCheck;

   name = "consecutive_sequence";
   src = ./.;

   buildInputs = [ libtool autoconf autoconf-archive automake gcc gtest ];

   preConfigure = ''
      libtoolize
      aclocal
      autoheader
      autoconf
      automake --add-missing
   '';

   hardeningDisable = [ "all" ];
}

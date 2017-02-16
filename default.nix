{ system ? builtins.currentSystem }:

let
   pkgs = import <nixpkgs> { inherit system; };

   callPackage = pkgs.lib.callPackageWith (pkgs);

   self = {
      classes = {
         product_inventory = callPackage ./classes/product_inventory { };
      };
   };
in

self.classes

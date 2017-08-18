(* Mathematica Package *)
(* Created by Mathematica Plugin for IntelliJ IDEA *)

(* :Title: FaddeevaM *)
(* :Context: FaddeevaM` *)
(* :Author: patrick *)
(* :Date: 2017-08-18 *)

(* :Package Version: 0.1 *)
(* :Mathematica Version: *)
(* :Copyright: (c) 2017 patrick *)
(* :Keywords: *)
(* :Discussion: *)

BeginPackage["FaddeevaM`"];

FaddeevaW::usage = "FaddeevaW[z] calculated Exp[-z^2] (1 - Erf[-I*z]) for complex z";
FaddeevaWIm::usage = "FaddeevaW[z]";
FaddeevaErfcx::usage = "FaddeevaErfcx[z]";
FaddeevaErfcxRe::usage = "FaddeevaErfcxRe[x]";
FaddeevaErf::usage = "FaddeevaErf[z]";
FaddeevaErfRe::usage = "FaddeevaErfRe[x]";
FaddeevaErfi::usage = "FaddeevaErfi[z]";
FaddeevaErfiRe::usage = "FaddeevaErfi[x]";
FaddeevaErfc::usage = "FaddeevaErfc[z]";
FaddeevaErfcRe::usage = "FaddeevaErfc[x]";
FaddeevaDawson::usage = "FaddeevaDawson[z]";
FaddeevaDawsonRe::usage = "FaddeevaDawsonRe[x]";

Begin["`Private`"];

Needs["CCompilerDriver`"];

packageAbort[] := (
  End[];
  EndPackage[];
  Abort[];
);

$FadeevaLibrary = "libFaddeevaM";
$FadeevaLibraryPath = FileNameJoin[{DirectoryName[System`Private`$InputFileName], "LibraryResources", $SystemID}];

rebuild[] := Module[{sources},
  sources = FileNameJoin[{DirectoryName[System`Private`$InputFileName], "LibraryResources", "Source", #}] & /@
  {"Faddeeva.c", "MMAFaddeeva.c"};

  Check[
    CreateLibrary[
      sources,
      $FadeevaLibrary,
      "ShellCommandFunction" :> Print,
      "ShellOutputFunction" :> Print,
      "TargetDirectory" -> $FadeevaLibraryPath
    ],
    $Failed
  ]
];

createLibraryFunction[{lib_,name_, arg_, result_}] := Module[{llFunc},
  llFunc = LibraryFunctionLoad[lib, name, {arg}, result];
  With[{f = llFunc},
    Compile[{{x, arg, 0}},
      f[x], Parallelization -> True, RuntimeAttributes -> {Listable}
    ]
  ]
];

If[Not@MemberQ[$LibraryPath, $FadeevaLibraryPath],
  AppendTo[$LibraryPath, $FadeevaLibraryPath];
];
$FadeevaLibraryFound = FindLibrary[$FadeevaLibrary];

FaddeevaM::noBLib = "No Faddeeva library found. Trying to rebuild one for you..";
FaddeevaM::noBuild = "Couldn't build library. Giving up..";
If[$FadeevaLibraryFound === $Failed,
  Message[FaddeevaM::noBLib];
  $status = rebuild[];
  If[$status === $Failed || ($FadeevaLibraryFound = FindLibrary[$FadeevaLibrary]) === $Failed,
    Message[FaddeevaM::noBuild];
    packageAbort[];
  ]
];

FaddeevaW = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_w", _Complex, Complex}];
FaddeevaErfcx = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_erfcx", _Complex, Complex}];
FaddeevaErf = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_erf", _Complex, Complex}];
FaddeevaErfi = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_erfi", _Complex, Complex}];
FaddeevaErfc = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_erfc", _Complex, Complex}];
FaddeevaDawson = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_Dawson", _Complex, Complex}];

FaddeevaWIm = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_w_im", _Real, Real}];
FaddeevaErfcxRe = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_erfcx_re", _Real, Real}];
FaddeevaErfRe = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_erf_re", _Real, Real}];
FaddeevaErfiRe = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_erfi_re", _Real, Real}];
FaddeevaErfcRe = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_erfc_re", _Real, Real}];
FaddeevaDawsonRe = createLibraryFunction[{$FadeevaLibraryFound, "m_Faddeeva_Dawson_re", _Real, Real}];


End[]; (* `Private` *)

EndPackage[];
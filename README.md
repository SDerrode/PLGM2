#PLGM means _Pairwise Linear Gaussian Model_.

**Programs** written by <valerian.nemesin@gmail.com>

**README.markdown** written by <stephane.derrode@ec-lyon.fr>    

**Remarks** : 

  1. Papers explaining the algorithms can be found in [Val&eacute;rian N&eacute;mesin](http://www.fresnel.fr/perso/nemesin/index.php?url=publi.php "Publications") and in [St&eacute;phane Derrode](http://perso.ec-lyon.fr/derrode.stephane/Research.php) web pages (or [here](https://liris.cnrs.fr/membres?idn=sderrode)).

  2. Note that [a demo of PLGM algorithms](http://www.fresnel.fr/perso/nemesin/index.php?url=demo.php&demo=PKF.php) still works (how long ?) to test the EM algorithm (without constraint). Don't be afraid if the figures are missing, you can still download the generated and estimated data using the link! **Remark**  At the time of publication the Web site of Institut Fresnel (where the demo is hosted) is not working, but we can expect that to be a temporal problem and all went OK in a few hours or days.

  3. A new front-end for Python and Matlab is being written and should appear in the next week to easy the parametrization of Partial learning configuration files. 


##1. Compile all programs

  1. From the root repository of the project, change options in `./compilation.mk` and in `./tkalman_c/Applications/options.mk` to suit your needs, especially la variable `APP_DIR` must indicate where applications will be stored (but default should be OK).

  2. Install [gsl library](http://www.gnu.org/software/gsl/ "GNU Scientific Library>") and `pkg-config`. For GSL you need the `dev` library (meaning that you should also install GSL headers files for compilation).

  3. On Ubuntu, you need to install the package `xutils-dev` for the command `makedepend` used by the makefiles. Install it using `sudo apt install xutils-dev`.

  4. Then `make`, or `make forced`. If all went well, the programs to run should be in `APP_DIR`.


##2. Test Kalman programs with Octave scripts

  1. Go to `Octave` repository and run `octave` (should be installed).

  2. Open one experiment from `exp_*.m` files (start with `exp_couple.m` for example), and change option according to your needs. Then run. A repository called `Resultats` should hold the results, with files and figures in png format.


**Good luck!**

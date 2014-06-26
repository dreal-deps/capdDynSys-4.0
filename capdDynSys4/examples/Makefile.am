include ${capdMake}/make/common_programs_makefile.mkf

SUBDIRS=cndemo diffIncldemo encloseTrajectory integrate newton coveringRelation maps odes odesrig poincare

if HAVE_capdkrak
   SUBDIRS+= graphicalSet taylor pointst
endif

if HAVE_mpcapdDynSys
   SUBDIRS += multiPrecision
endif

if HAVE_CXX11
   SUBDIRS += RosslerPeriodicOrbit LorenzPeriodicOrbit RosslerChaoticDynamics
endif

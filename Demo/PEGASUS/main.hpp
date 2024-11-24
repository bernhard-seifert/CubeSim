

// DEMO - PEGASUS


// Includes
#include <CubeSim/module/albedo.hpp>
#include <CubeSim/module/ephemeris.hpp>
#include <CubeSim/module/gravitation.hpp>
#include <CubeSim/module/light.hpp>
#include <CubeSim/module/magnetics.hpp>
#include <CubeSim/module/motion.hpp>
#include <CubeSim/celestial_body/earth.hpp>
#include <CubeSim/celestial_body/mars.hpp>
#include <CubeSim/celestial_body/moon.hpp>
#include <CubeSim/celestial_body/sun.hpp>
#include <CubeSim/system.hpp>
#include <CubeSim/simulation.hpp>
#include <CubeSim/part/box.hpp>
#include "ADCS/interface.hpp"
#include "ADCS/task.hpp"
#include "system/adapter_torquer.hpp"
#include "system/ADXL330.hpp"
#include "system/HMC5983.hpp"
#include "system/L3G4200D.hpp"
#include "system/OEM615.hpp"
#include "system/sidepanel_torquer.hpp"
#include "system/TEMD6200FX01.hpp"
#include "system/monitor.hpp"


// Class PegasusADCS
class PegasusADCS : public CubeSim::System
{
public:

   // Clone
   virtual System* clone(void) const;

private:

   // Behavior
   virtual void _behavior(void);

   // Initialization
   virtual void _init(void);
};

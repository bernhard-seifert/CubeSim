

// CUBESIM - CAD


// Includes
#include <iomanip>
#include <sstream>
#include "cad.hpp"
#include "part/box.hpp"
#include "part/cone.hpp"
#include "part/cylinder.hpp"
#include "part/prism.hpp"
#include "part/sphere.hpp"


// Export Code
const std::string CubeSim::CAD::code(void) const
{
   // Code
   std::stringstream code;

   // Insert Header
   code << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl << "<!DOCTYPE X3D PUBLIC \"ISO//Web3D//DTD X3D " <<
      "3.0//EN\" \"http://www.web3d.org/specifications/x3d-3.0.dtd\">" << std::endl << "<X3D profile=\"Immersive\" " <<
      "version=\"3.0\">" << std::endl << "<Scene>" << std::endl;

   // Parse Assembly List
   for (auto assembly = _assembly.begin(); assembly != _assembly.end(); ++assembly)
   {
      // Insert Code of Assembly
      code << _code(**assembly);
   }

   // Parse Celestial Body List
   for (auto celestial_body = _celestial_body.begin(); celestial_body != _celestial_body.end(); ++celestial_body)
   {
      // Insert Code of Celestial Body
      code << _code(**celestial_body);
   }

   // Parse Part List
   for (auto part = _part.begin(); part != _part.end(); ++part)
   {
      // Insert Code of Part
      code << _code(**part);
   }

   // Parse Spacecraft List
   for (auto spacecraft = _spacecraft.begin(); spacecraft != _spacecraft.end(); ++spacecraft)
   {
      // Insert Code of Spacecraft
      code << _code(**spacecraft);
   }

   // Parse System List
   for (auto system = _system.begin(); system != _system.end(); ++system)
   {
      // Insert Code of System
      code << _code(**system);
   }

   // Insert Footer
   code << "</Scene>" << std::endl << "</X3D>" << std::endl;

   // Return Code
   return code.str();
}


// Export Code of Assembly
const std::string CubeSim::CAD::_code(const Assembly& assembly) const
{
   // Code
   std::stringstream code;

   // Parse Assembly List
   for (auto assembly_ = assembly.assembly().begin(); assembly_ != assembly.assembly().end(); ++assembly_)
   {
      // Insert Code of Assembly
      code << _code(*assembly_->second);
   }

   // Parse Part List
   for (auto part = assembly.part().begin(); part != assembly.part().end(); ++part)
   {
      // Insert Code of Part
      code << _code(*part->second);
   }

   // Transform and return Code
   return _transform(code.str(), assembly.position(), assembly.rotation());
}


// Export Code of Celestial Body
const std::string CubeSim::CAD::_code(const CelestialBody& celestial_body) const
{
   // Code
   std::stringstream code;

   // Insert Color and Sphere
   code << "<Shape>" << std::endl << "<Appearance>" << std::endl << "<Material diffuseColor=\"1.0 1.0 1.0\" />" <<
      std::endl << "</Appearance>" << std::endl << std::fixed << std::setprecision(6) << "<Sphere radius=\"" <<
      celestial_body.radius() << "\" />" << std::endl << "</Shape>" << std::endl;

   // Transform and return Code
   return _transform(code.str(), celestial_body.position(), celestial_body.rotation());
}


// Export Code of Part
const std::string CubeSim::CAD::_code(const Part& part) const
{
   // Code, Position, Rotation
   std::stringstream code;
   Vector3D position;
   Rotation rotation;

   // Insert Color
   code << "<Shape>" << std::endl << "<Appearance>" << std::endl << "<Material diffuseColor=\"" <<
      (part.material().color().red() / 255.0) << " " << (part.material().color().green() / 255.0) << " " <<
      (part.material().color().blue() / 255.0) << "\" />" << std::endl << "</Appearance>" << std::endl;

   // Check Part
   if (dynamic_cast<const Part::Box*>(&part))
   {
      // Get Box
      const Part::Box& box = *dynamic_cast<const Part::Box*>(&part);

      // Insert Code of Box
      code << std::fixed << std::setprecision(6) << "<Box size=\"" << box.length() << " " << box.width() << " " <<
         box.height() << "\" />" << std::endl;

      // Update Position
      position = Vector3D(box.length() / 2.0, box.width() / 2.0, box.height() / 2.0);
   }
   else if (dynamic_cast<const Part::Cone*>(&part))
   {
      // Get Cone
      const Part::Cone& cone = *dynamic_cast<const Part::Cone*>(&part);

      // Insert Code of Cone
      code << std::fixed << std::setprecision(6) << "<Cone bottomRadius=\"" << cone.radius() << "\" height=\"" <<
         cone.height() << "\" />" << std::endl;

      // Update Rotation and Position
      rotation += Rotation(Vector3D::X, Constant::PI / 2.0);
      position += Vector3D(0.0, 0.0, cone.height() / 2.0);
   }
   else if (dynamic_cast<const Part::Cylinder*>(&part))
   {
      // Get Cylinder
      const Part::Cylinder& cylinder = *dynamic_cast<const Part::Cylinder*>(&part);

      // Insert Code of Cylinder
      code << std::fixed << std::setprecision(6) << "<Cylinder radius=\"" << cylinder.radius() << "\" height=\"" <<
         cylinder.height() << "\" />" << std::endl;

      // Update Rotation and Position
      rotation += Rotation(Vector3D::X, Constant::PI / 2.0);
      position += Vector3D(0.0, 0.0, cylinder.height() / 2.0);
   }
   else if (dynamic_cast<const Part::Prism*>(&part))
   {
      // Get Prism
      const Part::Prism& prism = *dynamic_cast<const Part::Prism*>(&part);

      // Insert Code of Prism
      code << "<Extrusion crossSection=\"";

      // Parse Vertices
      for (size_t i = 0; i <= prism.base().vertex().size(); ++i)
      {
         // Get Vertex
         Vector2D vertex = prism.base().vertex(i % prism.base().vertex().size());

         // Insert Vertex
         code << std::fixed << std::setprecision(6) << vertex.x() << " " << vertex.y() << " ";
      }

      // Insert Code of Prism
      code << std::fixed << std::setprecision(6) << "\" spine=\"0 0 " << prism.height() << " 0 0 0\" />" << std::endl;
   }
   else if (dynamic_cast<const Part::Sphere*>(&part))
   {
      // Get Sphere
      const Part::Sphere& sphere = *dynamic_cast<const Part::Sphere*>(&part);

      // Insert Code of Sphere
      code << std::fixed << std::setprecision(6) << "<Sphere radius=\"" << sphere.radius() << "\" />" << std::endl;
   }

   // Insert Shape
   code << "</Shape>" << std::endl;

   // Transform and return Code
   return _transform(_transform(code.str(), position, rotation), part.position(), part.rotation());
}


// Export Code of Spacecraft
const std::string CubeSim::CAD::_code(const Spacecraft& spacecraft) const
{
   // Code
   std::stringstream code;

   // Parse System List
   for (auto system = spacecraft.system().begin(); system != spacecraft.system().end(); ++system)
   {
      // Insert Code of System
      code << _code(*system->second);
   }

   // Transform and return Code
   return _transform(code.str(), spacecraft.position(), spacecraft.rotation());
}


// Export Code of System
const std::string CubeSim::CAD::_code(const System& system) const
{
   // Code
   std::stringstream code;

   // Parse System List
   for (auto system_ = system.system().begin(); system_ != system.system().end(); ++system_)
   {
      // Insert Code of System
      code << _code(*system_->second);
   }

   // Parse Assembly List
   for (auto assembly = system.assembly().begin(); assembly != system.assembly().end(); ++assembly)
   {
      // Insert Code of Assembly
      code << _code(*assembly->second);
   }

   // Transform and return Code
   return _transform(code.str(), system.position(), system.rotation());
}


// Transform Item
const std::string CubeSim::CAD::_transform(const std::string& code, const Vector3D& position,
   const Rotation& rotation) const
{
   // Code
   std::stringstream code_;
   code_ << code;

   // Check Rotation
   if (rotation.angle() != 0.0)
   {
      // Code
      std::string code__ = code_.str();
      code_ = std::stringstream();

      // Set Code
      code_ << std::fixed << std::setprecision(6) << "<Transform rotation=\"" << rotation.axis().x() << " " <<
         rotation.axis().y() << " " << rotation.axis().z() << " " << rotation.angle() << "\">" << std::endl << code__ <<
         "</Transform>" << std::endl;
   }

   // Check Position
   if (position != Vector3D())
   {
      // Code
      std::string code__ = code_.str();
      code_ = std::stringstream();

      // Set Code
      code_ << std::fixed << std::setprecision(6) << "<Transform translation=\"" << position.x() << " " << position.y()
         << " " << position.z() << "\">" << std::endl << code__ << "</Transform>" << std::endl;
   }

   // Return Code
   return code_.str();
}

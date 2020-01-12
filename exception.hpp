

// CUBESIM - EXCEPTION


// Preprocessor Directives
#pragma once


// Namespace CubeSim
namespace CubeSim
{
   // Class Exception
   class Exception;
}


// Class Exception
class CubeSim::Exception
{
public:

   // Class Failed
   class Failed;

   // Class Internal
   class Internal;

   // Class NotFound
   class NotFound;

   // Class Parameter
   class Parameter;

private:

   // Virtual Function for RTTI
   virtual void _func() {}
};


// Class Failed
class CubeSim::Exception::Failed : public Exception
{
};


// Class Internal
class CubeSim::Exception::Internal : public Exception
{
};


// Class NotFound
class CubeSim::Exception::NotFound : public Exception
{
};


// Class Parameter
class CubeSim::Exception::Parameter : public Exception
{
};

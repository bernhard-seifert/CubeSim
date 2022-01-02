

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

   // Class Parameter
   class Parameter;

private:

   // Virtual Function for RTTI
   virtual void _func(void);
};


// Class Failed
class CubeSim::Exception::Failed : public Exception
{
};


// Class Internal
class CubeSim::Exception::Internal : public Exception
{
};


// Class Parameter
class CubeSim::Exception::Parameter : public Exception
{
};


// Virtual Function for RTTI
inline void CubeSim::Exception::_func(void)
{
}

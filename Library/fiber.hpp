

// FIBER 1.0.1


// Includes
#include <windows.h>


// Preprocessor Directives
#pragma once


// Class Fiber
class Fiber
{
public:

   // Class Exception
   class Exception;

   // Function
   typedef void (*Function)(void* data);

   // Suspend
   static void suspend(void);

   // Constructor
   Fiber(Function function, void* data = nullptr);

   // Destructor
   ~Fiber(void);

   // Get Data
   void* data(void) const;

   // Check if done
   bool done(void) const;

   // Get Function
   Function function(void) const;

   // Run
   void run(void) const;

private:

   // Dispatcher
   static void CALLBACK _dispatch(void* parameter);

   // Variables
   static void* _main;
   bool _done;
   void* _address;
   void* _data;
   Function _function;
};


// Class Exception
class Fiber::Exception
{
public:

   // Class Internal
   class Internal;

private:

   // Virtual Function for RTTI
   virtual void _function() {}
};


// Class Internal
class Fiber::Exception::Internal : public Fiber::Exception
{
};


// Suspend
inline void Fiber::suspend(void)
{
   // Run Main Fiber
   SwitchToFiber(_main);
}


// Destructor
inline Fiber::~Fiber(void)
{
   // Delete Fiber
   DeleteFiber(_address);
}


// Get Data
inline void* Fiber::data(void) const
{
   // Return Data
   return _data;
}


// Check if done
inline bool Fiber::done(void) const
{
   // Return Flag
   return _done;
}


// Get Function
inline Fiber::Function Fiber::function(void) const
{
   // Return Function
   return _function;
}


// Run
inline void Fiber::run(void) const
{
   // Run Fiber
   SwitchToFiber(_address);
}

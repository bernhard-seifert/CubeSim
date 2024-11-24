

// FIBER 1.0.1


// Copyright (c) 2022 Bernhard Seifert
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sub-license, and / or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


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

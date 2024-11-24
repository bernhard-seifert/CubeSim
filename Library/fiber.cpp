

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
#include "fiber.hpp"


// Constructor
Fiber::Fiber(Function function, void* data) : _done(false), _data(data), _function(function)
{
   // Check Main Fiber
   if (!_main)
   {
      // Convert Thread to Fiber
      _main = ConvertThreadToFiber(nullptr);

      // Check Address
      if (!_main)
      {
         // Exception
         throw Exception::Internal();
      }
   }

   // Create Fiber
   _address = CreateFiber(0, _dispatch, this);

   // Check Address
   if (!_address)
   {
      // Exception
      throw Exception::Internal();
   }
}


// Dispatcher
void CALLBACK Fiber::_dispatch(void* parameter)
{
   // Get Fiber
   Fiber& fiber = *reinterpret_cast<Fiber*>(parameter);

   // Call Function
   fiber._function(fiber._data);

   // Set Flag
   fiber._done = true;

   // Loop
   for (;;)
   {
      // Return to Main Fiber
      Fiber::suspend();
   }
}


// Variables
void* Fiber::_main = nullptr;

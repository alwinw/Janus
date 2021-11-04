//
// DST Janus Library (Janus DAVE-ML Interpreter Library)
//
// Defence Science and Technology (DST) Group
// Department of Defence, Australia.
// 506 Lorimer St
// Fishermans Bend, VIC
// AUSTRALIA, 3207
//
// Copyright 2005-2021 Commonwealth of Australia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
// OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//

#define S_FUNCTION_NAME JanusSFunction
#define S_FUNCTION_LEVEL 2

#include <set>
#include <string>

#include <simstruc.h>
#include <Janus/Janus.h>

using namespace std;

// #define DEBUG_PRINT( ...) printf( __VA_ARGS__)
#define DEBUG_PRINT( ...)

template<typename _Kty, class _Pr = std::less<_Kty>, class _Alloc = std::allocator<_Kty>>
std::set<_Kty,_Pr,_Alloc> exclusive_to_first( std::set<_Kty,_Pr,_Alloc> s1, const std::set<_Kty,_Pr,_Alloc>& s2)
{
  for ( auto it = s1.begin(); it != s1.end(); ) {
    if ( s2.find( *it) == s2.end()) {
      ++it;
    }
    else {
      it = s1.erase( it);
    }
  }
  return s1;
}

enum PARAMS
{
  XML_FILENAME,
  INDVARS,
  DEPVARS,
  PARAM_COUNT
};

enum POINTERS
{
  JANUS,
  INDVARIDS,
  DEPVARIDS,
  POINTER_COUNT
};

static void mdlInitializeSizes( SimStruct* S)
{
  ssSetNumSFcnParams( S, PARAM_COUNT);
  if ( ssGetNumSFcnParams( S) != ssGetSFcnParamsCount( S)) return;

  ssSetSFcnParamTunable( S, XML_FILENAME, 0);
  ssSetSFcnParamTunable( S, INDVARS, 0);
  ssSetSFcnParamTunable( S, DEPVARS, 0);

  ssSetNumContStates( S, 0);
  ssSetNumDiscStates( S, 0);

  if ( !ssSetNumInputPorts( S, 1)) return;
  if ( !ssSetNumOutputPorts( S, 1)) return;

  // Get number of independent variables
  const mxArray* indvarArray = ssGetSFcnParam( S, INDVARS);
  if ( mxGetClassID( indvarArray) != mxCHAR_CLASS) {
    ssSetErrorStatus( S, "Independent varIDs must be a string array.");
    return;
  }
  const int nIndVars = mxGetM( indvarArray);
  DEBUG_PRINT( "nIndVars: %d\n", nIndVars);
  ssSetInputPortWidth( S, 0, nIndVars);

  // Get number of dependent variables
  const mxArray* depvarArray = ssGetSFcnParam( S, DEPVARS);
  if ( mxGetClassID( depvarArray) != mxCHAR_CLASS) {
    ssSetErrorStatus( S, "Dependent varIDs must be a string array.");
    return;
  }
  const int nDepVars = mxGetM( depvarArray);
  DEBUG_PRINT( "nDepVars: %d\n", nDepVars);
  ssSetOutputPortWidth( S, 0, nDepVars);

  ssSetInputPortRequiredContiguous( S, 0, false); 
  ssSetInputPortDirectFeedThrough( S, 0, 1);

  ssSetNumSampleTimes( S, 1);
  ssSetNumRWork( S, 0);
  ssSetNumIWork( S, 0);
  ssSetNumPWork( S, POINTER_COUNT);
  ssSetNumModes( S, 0);
  ssSetNumNonsampledZCs( S, 0);

  ssSetOptions( S, 0);
}

static void mdlInitializeSampleTimes( SimStruct* S)
{
  ssSetSampleTime( S, 0, CONTINUOUS_SAMPLE_TIME);
  ssSetOffsetTime( S, 0, 0.0);
}

#define MDL_START
static void mdlStart( SimStruct* S)
{
  ssGetPWork(S)[JANUS] = new janus::Janus;
  janus::Janus* janus = static_cast<janus::Janus*>( ssGetPWork(S)[JANUS]);

  int status, n;

  // Get filename and read into Janus
  const mxArray* filenameArray = ssGetSFcnParam( S, XML_FILENAME);
  const size_t filenameLength = mxGetM( filenameArray) * mxGetN( filenameArray) + 1;
  char* filename = static_cast<char*>( calloc( filenameLength, sizeof( char)));
  status = mxGetString( filenameArray, filename, filenameLength);
  DEBUG_PRINT( "filename: %s\n", filename);
  if ( status) {
    ssSetErrorStatus( S, "XML filename could not be read");
    return;
  }

  try {
    janus->setXmlFileName( filename);
    free( filename);
  } 
  catch ( std::exception &excep) {
    ssSetErrorStatus( S, excep.what());
    free( filename);
    return;
  }

  // Get independent variables
  const mxArray* indvarArray = ssGetSFcnParam( S, INDVARS);
  const int nIndVars = mxGetM( indvarArray);
  char** indVarIDs = static_cast<char**>( calloc( nIndVars, sizeof( char*)));
  const int indVarLength = mxGetM( indvarArray) * mxGetN( indvarArray) + 1;
  char* indVarBuf = static_cast<char*>( calloc( indVarLength, sizeof( char)));
  status = mxGetString( indvarArray, indVarBuf, indVarLength);
  if ( status) {
    ssWarning( S, "Independent varID strings are truncated.");
  }
  n = mxGetN( indvarArray);
  for ( int var = 0; var < nIndVars; ++var) {
    for ( int i = 0; i < n; ++i) {
      int iof = var + nIndVars * i;
      int len = -1;
      if ( indVarBuf[iof] == ' ') len = i + 1;
      if ( i + 1 == n) len = i + 2;
      if ( len != -1) {
        indVarIDs[var] = static_cast<char*>( calloc( len, sizeof( char)));
        indVarIDs[var][len-1] = '\0';
        for ( int k = 0; k < len - 1; ++k) {
          indVarIDs[var][k] = indVarBuf[var + nIndVars * k];
        }
        DEBUG_PRINT( "indVarIDs[%d]: %s\n", var, indVarIDs[var]);
        break;
      }
    }
  }
  ssSetPWorkValue( S, INDVARIDS, indVarIDs);
  free( indVarBuf);

  // Get dependent variables
  const mxArray* depvarArray = ssGetSFcnParam( S, DEPVARS);
  const int nDepVars = mxGetM( depvarArray);
  char** depVarIDs = static_cast<char**>( calloc( nDepVars, sizeof( char*)));
  const int depVarLength = mxGetM( depvarArray) * mxGetN( depvarArray) + 1;
  char* depVarBuf = static_cast<char*>( calloc( indVarLength, sizeof( char)));
  status = mxGetString( depvarArray, depVarBuf, depVarLength);
  if ( status) {
    ssWarning( S, "Dependent varID strings are truncated.");
  }
  n = mxGetN( depvarArray);
  for ( int var = 0; var < nDepVars; ++var) {
    for ( int i = 0; i < n; ++i) {
      int iof = var + nDepVars * i;
      int len = -1;
      if ( depVarBuf[iof] == ' ') len = i + 1;
      if ( i + 1 == n) len = i + 2;
      if ( len != -1) {
        depVarIDs[var] = static_cast<char*>( calloc( len, sizeof( char)));
        depVarIDs[var][len-1] = '\0';
        for ( int k = 0; k < len - 1; ++k) {
          depVarIDs[var][k] = depVarBuf[var + nDepVars * k];
        }
        DEBUG_PRINT( "depVarIDs[%d]: %s\n", var, depVarIDs[var]);
        break;
      }
    }
  }
  ssSetPWorkValue( S, DEPVARIDS, depVarIDs);
  free( depVarBuf);

  // Check that independent variables
  set<string> janusInputVars;
  const janus::VariableDefList& varDefList = janus->getVariableDef();
  for ( auto& v : varDefList) {
    if ( v.isInput()) janusInputVars.insert( v.getVarID());
  }

  set<string> thisInputVars;
  for ( int i = 0; i < nIndVars; ++i) {
    thisInputVars.insert( indVarIDs[i]);
  }

  const set<string> janusOnlyInputs = exclusive_to_first( janusInputVars, thisInputVars);
  if ( !janusOnlyInputs.empty()) {
    string errorMessage = "The following input variables are expected by the dataset:\n";
    for ( const string& s : janusOnlyInputs) errorMessage += s + "\n";
    ssWarning( S, errorMessage.c_str());
  }

  set<string> badInputs;
  for ( const string& s : thisInputVars) {
    auto v = janus->findVariableDef( s);
    if ( v && !v->isInput()) badInputs.insert( s);
  }
  if ( !badInputs.empty()) {
    string errorMessage = "The following input variables are not marked as inputs within the dataset:\n";
    for ( const string& s : badInputs) errorMessage += s + "\n";
    ssWarning( S, errorMessage.c_str());
  }

  // Check dependent variables
  set<string> badOutputs;
  for ( int i = 0; i < nDepVars; ++i) {
    if ( !janus->findVariableDef( depVarIDs[i])) badOutputs.insert( depVarIDs[i]);
  }
  if ( !badOutputs.empty()) {
    string errorMessage = "The following output variables are not provided by the dataset:\n";
    for ( const string& s : badOutputs) errorMessage += s + "\n";
    ssWarning( S, errorMessage.c_str());
  }
}

static void mdlOutputs( SimStruct *S, int_T tid)
{
  janus::Janus* janus = static_cast<janus::Janus*>( ssGetPWork(S)[JANUS]);
  char** indVarIDs = static_cast<char**>( ssGetPWork(S)[INDVARIDS]);
  char** depVarIDs = static_cast<char**>( ssGetPWork(S)[DEPVARIDS]);

  const mxArray* indvarArray = ssGetSFcnParam( S, INDVARS);
  const int nIndVars = mxGetM( indvarArray);
  const mxArray* depvarArray = ssGetSFcnParam( S, DEPVARS);
  const int nDepVars = mxGetM( depvarArray);

  InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs( S,0);
  real_T* y = ssGetOutputPortRealSignal( S, 0);

  for ( int i = 0; i < nIndVars; ++i) {
    real_T u = *uPtrs[i];
    auto varDef = janus->findVariableDef( indVarIDs[i]);
    if ( varDef) varDef->setValueMetric( u);
  }

  for ( int i = 0; i < nDepVars; ++i) {
    auto varDef = janus->findVariableDef( depVarIDs[i]);
    if ( varDef) y[i] = varDef->getValueMetric();
  }
}

static void mdlTerminate( SimStruct *S)
{
  janus::Janus* janus = static_cast<janus::Janus*>( ssGetPWork(S)[JANUS]);
  char** indVarIDs = static_cast<char**>( ssGetPWork(S)[INDVARIDS]);
  char** depVarIDs = static_cast<char**>( ssGetPWork(S)[DEPVARIDS]);

  delete janus;

  const mxArray* indvarArray = ssGetSFcnParam( S, INDVARS);
  const int nIndVars = mxGetM( indvarArray);
  for ( int i = 0; i < nIndVars; ++i) free( indVarIDs[i]);
  free( indVarIDs);

  const mxArray* depvarArray = ssGetSFcnParam( S, DEPVARS);
  const int nDepVars = mxGetM( depvarArray);
  for ( int i = 0; i < nDepVars; ++i) free( depVarIDs[i]);
  free( depVarIDs);
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include <simulink.c>      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


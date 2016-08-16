
#include <stdio.h>
#include <string.h>

#ifndef __again__
#include "again.h"
#endif


AGainProgram::AGainProgram ()
{
	// default Program Values
	fGain = 0.75;

	strcpy (name, "Init");
}


AGain::AGain (audioMasterCallback audioMaster)
	: AudioEffectX (audioMaster, kNumPrograms, kNumParams)
{
  programs = new AGainProgram[numPrograms];
	fGain = 0.75;

	if (programs) {
		setProgram (0);
  }

	setNumInputs (2);
	setNumOutputs (2);

  setUniqueID ('5864');

  resume ();
}


AGain::~AGain ()
{
	if(buffer) {
		delete[] buffer;
  }

	if(programs) {
		delete[] programs;
  }
}


void AGain::setProgram (VstInt32 program)
{
  AGainProgram* ap = &programs[program];
	curProgram = program;
	setParameter(kGain, ap->fGain);	
}

void AGain::setProgramName (char *name)
{
	strcpy(programs[curProgram].name, name);
}


void AGain::getProgramName (char *name)
{
	if(!strcmp (programs[curProgram].name, "Init")) {
		sprintf (name, "%s %d", programs[curProgram].name, curProgram + 1);
  } else {
		strcpy (name, programs[curProgram].name);
  }
}

bool AGain::getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text)
{
	if(index < kNumPrograms) {
		strcpy(text, programs[index].name);
		return true;
	}
	return false;
}


void AGain::resume ()
{
	AudioEffectX::resume();
}


void AGain::setParameter (VstInt32 index, float value)
{
  AGainProgram* ap = &programs[curProgram];

	switch (index) {
		case kGain: fGain = ap->fGain = value; break;
	}
}


float AGain::getParameter (VstInt32 index)
{
	float v = 0;

	switch (index) {
		case kGain: v = fGain; break;
	}
	return v;
}


void AGain::getParameterName (VstInt32 index, char *label)
{
	switch (index) {
		case kGain: strcpy (label, "Gain"); break;
	}
}


void AGain::getParameterDisplay (VstInt32 index, char *text)
{
	switch (index) {
		case kGain: float2string (fGain, text, kVstMaxParamStrLen);	break;
	}
}


void AGain::getParameterLabel (VstInt32 index, char *label)
{
	switch (index) {
		case kGain: strcpy (label, "");	break;
	}
}


bool AGain::getEffectName (char* name)
{
  strcpy (name, "AGain");
	return true;
}


bool AGain::getProductString (char* text)
{
  strcpy (text, "AGain");
	return true;
}


bool AGain::getVendorString (char* text)
{
  strcpy (text, "Company Name");
	return true;
}


void AGain::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames)
{
	VstInt32 current = sampleFrames;
	while (--current >= 0) {
    outputs[0][current] = inputs[0][current] * fGain;
    outputs[1][current] = inputs[1][current] * fGain;
	}
}

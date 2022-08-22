#pragma message "---------- BUILDING SD CARD SUPPORT ----------"

#include "KeckACS.h"

/* ----------------------------------------------------------------------------------------------------------- */
/* Append data to the current capture */
void SDAppendMotionGalil(uint32_t apc, uint32_t current) {

  /* Stop capturing after max (10k) entries */
  if (sample_index > MAX_SAMPLES) 
    return;

  samples[sample_index].ts = micros();
  samples[sample_index].apc = apc;  
  samples[sample_index].current = current;

  sample_index++;
  SamplesAreCypress = false;
}


/* ----------------------------------------------------------------------------------------------------------- */
void SDAppendMotionCypress(uint32_t apc, int16_t current) {

  /* Stop capturing after max (10k) entries */
  if (sample_index > MAX_SAMPLES) 
    return;

  samples[sample_index].ts = micros();
  samples[sample_index].apc = apc;  
  samples[sample_index].current = current;

  sample_index++;
  SamplesAreCypress = true;
}


/* ----------------------------------------------------------------------------------------------------------- */
/* Record the start and stop times in the JSON structure */
void SDSetTimes(uint32_t startTime, uint32_t stopTime) {

  samples_json["meta"]["start"] = startTime;
  samples_json["meta"]["stop"] = stopTime;

}

/* ----------------------------------------------------------------------------------------------------------- */
/* Get the next file in the numeric sequence for the provided prefix (nominally GAL or CYP) */
int SDGetNextFilenumber(const char *prefix) {

  // Allow for 10k files per prefix
  #define MAX_FILE_INDEX 4

  int result;
  int val = 0;
  int maxval = -1;
  File root;

  /* Looking for 4 character numeric strings */
  const char *filename;
  char indexstr[MAX_FILE_INDEX];
  char subtext[10];  // Allow for 10 char prefixes

  /* Init the SD card */
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SDGetNextFilename: SD initialization failed, cannot init!");
    return 0;
  }

  /* Only check the root dir */
  root = SD.open("/");
  Serial.println(">>> Reading root filesystem of SD card");
  
  while (true) {

    File entry =  root.openNextFile();

    if (!entry) {
      // no more files
      break;
    }

    /* Extract the prefix off the filename */
    filename = entry.name();
    bzero(subtext, 10);
    strncpy(subtext, filename, strlen(prefix));

    //Serial.printf("subtext: _%s_    filename: _%s_   prefix: _%s_ \n", subtext, filename, prefix);

    /* Check the prefix of the file to see if it matches the sequence we're looking for */
    result = strcmp(prefix, subtext);

    if (result == 0) {
      
      /* A match! Get the 4 digit nunber out of the file */
      strncpy(indexstr, filename+strlen(prefix), MAX_FILE_INDEX);

      if (sscanf(indexstr, "%d", &val) > 0) {

        if (val > maxval) {
          maxval = val;
        }
      }
    }

    entry.close();
  }

  /* Increment the max by one before returning */
  maxval++;

  Serial.printf(">>> Next file index is %d\n", maxval);
  return maxval;
}


/* ----------------------------------------------------------------------------------------------------------- */
void SDWriteMotion(void) {

  #define file_tag "/ACS"
  char file_name[32];
  char file_label[32];
  uint16_t bytes_written;
  uint16_t file_number = 0;
  uint32_t i;


  /* Init the SD card */
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("SD initialization failed, cannot write a file!");
    return;
  }

  /* Get the last filename off the SD card */
  file_number = SDGetNextFilenumber("ACS");

  /* Build the new filename */
  strcpy(file_name, file_tag); // Start with the root dir and "ACS"
  
  sprintf(file_label, "%04d", file_number);  // Add the numeric value   
  strcat(file_name, file_label);  
  
  strcat(file_name, ".json");  // Finally, the suffix

  // Open the file we want to write, remove anything already in there
  file = SD.open(file_name, FILE_WRITE);
  file.seek(0);
  file.truncate();
  
  if (!file) {
    Serial.printf("SD open failed, cannot write file '%s'\n", file_name);
    return;
  }
   
  /* Write the JSON out to the file */  
  for (i = 0; i < sample_index; i++) {
    
    /* Convert struct to JSON */
    samples_json["samples"][i]["ts"] = samples[i].ts;
    samples_json["samples"][i]["apc"] = samples[i].apc;

    /* The Galil needs current scaled, the Cypress does not */
    if (SamplesAreCypress) {
      samples_json["samples"][i]["current"] = float(samples[i].current);
    } else {
      samples_json["samples"][i]["current"] = float(samples[i].current) * 0.004;
    }
  }

  bytes_written = serializeJsonPretty(samples_json, file);

  /* Done writing file */
  file.close();

  /* Done with the capture buffer, too */
  samples_json.clear();
  bzero(samples, sizeof(samples));
  sample_index = 0;

  Serial.printf(">>> SD WRITE COMPLETE, %d BYTES WRITTEN TO %s\n", bytes_written, file_name);
  Serial.printf("-----------------------------------------------------------\n");

}

#pragma message "---------- BUILDING SD CARD SUPPORT - DONE ----------"

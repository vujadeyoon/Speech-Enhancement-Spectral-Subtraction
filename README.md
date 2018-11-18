# Speech enhancement for Spectral Subtraction (SS)
C implementation of spectral subtraction for speech enhancement

## Table of contents
1. [Development environments](#dev_env)
2. [Usages](#usage)
3. [Note](#note)

## Development environments <a name="dev_env"></a>
* Coding language: C language
* Integrated Development Environment(IDE): Microsoft Visual Studio 2017

## Usages <a name="usage"></a>
* Noisy signal file name: speech_noisy.raw
* Desirged output signal file name: speech_cleaned.raw
* Frame size: 256
* Base frame size to estimate noise signal: 5
```c
User-dir:\SpeechEnhancement\Release> SpeechEnhancement.exe speech_noisy.raw speech_cleaned.raw 256 5
```

## Note <a name="note"></a>
* Please note that the PESQ for evaluating the performance will be provided soon.

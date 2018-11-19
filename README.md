# Spectral Subtraction (SS) for speech enhancement
C implementation of spectral subtraction for speech enhancement

## Table of contents
1. [Development environments](#dev_env)
2. [Usages](#usage)
3. [Performance](#performance)

## Development environments <a name="dev_env"></a>
* Coding language: C language
* Integrated Development Environment(IDE): Microsoft Visual Studio 2017

## Usages <a name="usage"></a>
* Noisy signal file name: speech_noisy.raw (Sampling rate: 8000HZ)
* Desirged output signal file name: speech_cleaned.raw
* Frame size: 256
* Base frame size to estimate noise signal: 5
```c
User-dir:\SpeechEnhancement\Release> SpeechEnhancement.exe speech_noisy.raw speech_cleaned.raw 256 5
```

## Performance <a name="performance"></a>
* Perceptual Evaluation of Speech Quality (PESQ): 3.35

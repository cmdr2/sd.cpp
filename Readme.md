Experiments with compiling [stable-diffusion.cpp](https://github.com/leejet/stable-diffusion.cpp) along with a simple C++ wrapper program.

It's obviously better to use the pre-built sd.cpp libraries (from their releases page), loaded as a dynamic library. This experiment was purely to try compiling sd.cpp from scratch, as a sub-module of a project.

## Compile
### CPU-only compile:

```
cmake
cmake --build . --config Release
```

### CUDA compile:

Install the [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads). Also I had to [copy some files around to make it work](https://github.com/NVlabs/tiny-cuda-nn/issues/164#issuecomment-1280749170), and point the `CUDAToolkit_ROOT` environment variable to where the CUDA toolkit was installed (for e.g. `C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v12.6`).

It only works with MSVC, since it requires `cl.exe`. Installed Visual Studio Community edition, with Desktop C++ support. Then included that in the `PATH` environment variable.

Compiled using:
```
cmake -DSD_CUBLAS=ON
cmake --build . --config Release
```

## Run

You can run `sd2.exe`, which will load the model from the hard-coded path in `src/main.cpp`, and generate a test image.

It doesn't save the image to disk currently, since this is currently just an experiment to see if things work together.

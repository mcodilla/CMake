vs-msbuild-extractor-hook
-------------------------

* :ref:`Visual Studio Generators` now support a build-time
  :variable:`CMAKE_EXPORT_COMPILE_COMMANDS` workflow when using
  :option:`cmake --build <cmake--build --build>`.  CMake enables MSBuild
  binary logging and invokes the external ``msbuild-extractor-tool``
  to publish observed compiler commands.  The
  :variable:`CMAKE_VS_MSBUILD_EXTRACTOR` cache entry can select the tool.

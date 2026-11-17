CMAKE_VS_MSBUILD_EXTRACTOR
--------------------------

.. versionadded:: 4.5

Optional cache ``FILEPATH`` specifying the external ``msbuild-extractor-tool``
executable used by :ref:`Visual Studio Generators` when
:variable:`CMAKE_EXPORT_COMPILE_COMMANDS` is enabled.

If unset or empty, CMake searches beside its own executable and on ``PATH``.
The tool is resolved when :option:`cmake --build <cmake--build --build>` runs,
not during project configuration.  CMake does not install or download it.

The tool must support binlog export with ``--output-file``.  Exit codes
``0`` and ``2`` indicate publication, ``3`` indicates no new compiler work
with the previous database preserved, and other outcomes fail the requested
export.  An existing native build failure remains the build's exit status.

CMAKE_EXPORT_COMPILE_COMMANDS
-----------------------------

.. versionadded:: 3.5

Enable/Disable export of compile commands.

With :ref:`Makefile Generators` and :ref:`Ninja Generators`, enabling this
option generates a ``compile_commands.json`` file containing the exact
compiler calls for all translation units of the project in machine-readable
form.  The format of the JSON file looks like:

.. code-block:: javascript

  [
    {
      "directory": "/home/user/development/project",
      "command": "/usr/bin/c++ ... -c ../foo/foo.cc",
      "file": "../foo/foo.cc",
      "output": "../foo.dir/foo.cc.o"
    },

    ...

    {
      "directory": "/home/user/development/project",
      "command": "/usr/bin/c++ ... -c ../foo/bar.cc",
      "file": "../foo/bar.cc",
      "output": "../foo.dir/bar.cc.o"
    }
  ]

This is initialized by the :envvar:`CMAKE_EXPORT_COMPILE_COMMANDS` environment
variable, and initializes the :prop_tgt:`EXPORT_COMPILE_COMMANDS` target
property for all targets.

.. note::
  This option currently does not work well in combination with
  the :prop_tgt:`UNITY_BUILD` target property or the
  :variable:`CMAKE_UNITY_BUILD` variable.

Visual Studio Generators
^^^^^^^^^^^^^^^^^^^^^^^^

.. versionadded:: 4.5

For :ref:`Visual Studio Generators`, set this option in the cache to enable
export after :option:`cmake --build <cmake--build --build>`.  The environment
variable can initialize that cache entry as described above.

CMake enables MSBuild binary logging and, after MSBuild exits, invokes the
external ``msbuild-extractor-tool`` executable to read the logs and publish
``compile_commands.json`` in the top-level build directory.  CMake does not
reconstruct compiler commands or write the database.  The extractor must
support ``--binlog``, ``--export-compile-commands``, ``--variant-policy first``,
``--allow-failed-build``, and ``--output-file``.  See
:variable:`CMAKE_VS_MSBUILD_EXTRACTOR` for executable discovery.

The database contains compilations observed in that build, not a complete
inventory of project sources.  A selected-target or incremental build can
replace a broader snapshot with a narrower one.  A no-work build preserves
the previous file, if any.  Only configurations actually built are included;
the most recent publication replaces the shared database.  Failed builds can
export attempted compilations without changing the build's failure status.

This workflow does not support direct MSBuild invocations, Visual Studio IDE
or ``devenv`` builds, or per-target :prop_tgt:`EXPORT_COMPILE_COMMANDS`
selection.  Clean-only, restore-only, and compiler-check builds do not export.
Turning this option off does not remove a previous database.

Private capture directories are created under
``CMakeFiles/CompileCommands``.  They are removed after a successful build
and export, and retained on failure for diagnosis.  User-requested binary
logs are not removed.  MSBuild must support binary logging and, when other
binary loggers are requested, additive binary logging.

Other Generators
^^^^^^^^^^^^^^^^

This option is ignored by generators not described above.

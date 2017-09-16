
The simplest way to get this project working under Visual Studio is to utilise the vcpkg project to manage your libraries for you.
It also handles copying external lib files into the build directory!

https://github.com/Microsoft/vcpkg

Clone the vcpkg repo locally, to where ever you want to store your external libraries.
Follow the installation instructions for the project.
A few things to keep in mind:

0. Where ever you clone the repo and run the program from is where the libs will be installed.

1. To target 32-bit or 64-bit platforms, you need the 32-bit or 64-bit library, respectively.
	By default, vcpkg installs 32-bit libraries.
	To install the 64-bit version, you have two options:
		i. Postfix the package name with the platform: "sfml:x64-windows"
		ii. Set up an environment variable for VCPKG_DEFAULT_TRIPLET=x64-windows
			a. This will default installations to be 64 bit, so
				For 32-bit installs, replace the above x64's with x86's.

2. Don't forget to run `vcpkg.exe integrate install`, and read the output! 
	There's a file path you'll need to include for vcpkg libraries to be included properly.
	It needs to be included as a CMake command argument for the -D flag

3. We're using CMake for this project. It is the standard C++ build tool. Visual Studio CMake support is fairly new and can be
	utilised by opening the project as a folder, not as a visual studio solution.
	Once Visual Studio finds the CMakeLists.txt file, the editor will present you with a CMake menu list between Project and Build.
	This list is your home for managing CMake, under it you'll first find two entries of primary interest:
		i. Cache (<target-configuration> Only) ->  Generate -> CMakeLists.txt (Project BulletHell)
			This will generate the CMake Cache for the currently selected target-configuration.
		ii. Change CMakeSettings -> CMakeLists.txt (Project BulletHell)
			This will open a CMakeSettings.json file where you can edit your system specific configurations for CMake.
			Of most interest is the inclusion of the VCPKG Toolchain CMake file.
			In each target configuration, for the "cmakeCommandArgs" attribute, do not forget to include: 
				"-DCMAKE_TOOLCHAIN_FILE=\"C:/<path-to-yours>/vcpkg/scripts/buildsystems/vcpkg.cmake\""
	After generating a cache, this menu offers a few new menu selections, of particular interest are:
		i. Build All
			Used to build all targets specified in the CMake Configs
		ii. Cache (<target-configuration> Only) -> Delete Cache Folders -> CMakeLists.txt (Project BulletHell)
			Used to clear the cache. Used when things get buggy, mostly when you're tweaking with CMakeLists.txt or CMakeSettings.json
			Under current configurations, the Build directory for each target-configuration is located in this cache!
			Clearing the Cache will delete your most recent build for the target-configuration you have selected!


4. CMakeSettings.json is not a CMake file, it is a Visual Studio one.
	The default comes with 4 target configurations, build/release for x86/x64.
	Using vcpkg, you only need to include "-DCMAKE_TOOLCHAIN_FILE=\"C:/<path-to-yours>/vcpkg/scripts/buildsystems/vcpkg.cmake\""
	  in your "cmakeCommandArgs" attribute for each target-config.
	These target configurations are easily swappable in the IDE's interface, via a drop-down list next to the large debug button.

5. The build button is under CMake. The run button needs a target selected. For most cases, this will be "bullet.exe".


Specifically, for this project, you will need to execute, at a minmum,
the following commands, at a command prompt with administrator rights:

`bootstrap-vcpkg.bat`
`vcpkg.exe integrate install`
`vcpkg.exe install sfml`
`vcpkg.exe install boost`

Consider the need of the following:
`vcpkg.exe install sfml:x86-windows`
`vcpkg.exe install boost:x86-windows`
`vcpkg.exe install sfml:x64-windows`
`vcpkg.exe install boost:x64-windows`

I've read that you need to run `vcpkg.exe integrate install` only once.
I've also read that running it multiple times helps?
I've run it multiple times.

After you get the project working, we also make use of clang-format.
Visual studio has an extension (Tools -> Extensions and Updates) (Online, search "ClangFormat")

This will add two commands to the Tools menu, format selection and format document.
There is a configuration in (Tools -> Options -> LLVM/Clang) to enable auto-format on save.

Consider using (Tools -> Customize) to add useful buttons, like Build All, Format Document,
and Run Without Debugger, to the end of the upper-most toolbar, or make your own.


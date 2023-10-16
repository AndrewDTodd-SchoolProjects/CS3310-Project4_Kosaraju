# Project4_Kosaraju

Steps to build
prolog: though this step isn't strictly necessary to actually build the project it helps to make sure the user is in the right directory and all necessary configuration files have been downloaded correctly
  in the bash terminal navigate to the directory of the cloded repository. For isntance home/CS4380.
  in this root directory for the repo there should be a CMakePresets.json document.
  verify its contents are correct by running the following command
  
    cmake --list-presets=all

  after running this command you should see a dialog saying that the available configure presets are
  
    on windows:
      "windows-x64-debug" and "windows-x64-release"

    on linux:
      "linux-x64-debug" and "linux-x64-release"

Step 1:
  This is where the actual necessary steps to build and run begin

  while in the root directory of the repositories clone (such as home/CS3310-Project2_MergeSortInversionCount) run the following command to set the cmake build configuration
    
      on windows
        cmake --preset windows-x64-release (or debug for debug build)

      on linux
        cmake --preset linux-x64-release (or debug for debug build)

  Cmake will configure for the build now. The last line of the dialog will tell you what directory the build cache files have been made in.
      
      It will be ${root}/build/Release (or Debug) (CS3310-Project4_Kosaraju/build/Release)

 Step 2:
   now run the following command
   
     cmake --build ./build/Release (or Debug if debug build was specified previously)

   you will see a build process proceed
   upon completion navigate to the build/Release (or Debug) directory with the following command

     cd build/Release (or Debug)

 Step 3:
   the built executables can now be run

   To run the Kosaraju program
    
      on windows
        .\Kosaraju.exe <optional debug indicator (-d)> <optional file-path> <optional output count num> (file-path is to a file with new line deliminated list of edges, such as those in TestFiles directory)

      on linux
        ./Kosaraju <optional debug indicator (-d)> <optional file-path> <optional output count num> (same as on windows for file-path option)  

  Upon completion the program will report the top five (or optional count num) SCCs with the most elements

# Boost libraries which were build and not just headers.
#BOOST_LIBS = ['libboost_filesystem.so', 'libboost_system.so', 'libboost_random.so']

# update this according to the boost installation
#BOOST_LIBS_PATH = '/usr/local/lib/' 	

# Project definitions
include = '#/include'	# Header files location
src     = '#/src'		# Source files location
build   = '#/build'		# Object files location
bin     = '#/bin'		# Executable files location
program = 'trees'		# Name of executable
	
#program = 'Trees-cf-0.35-noise-1.0'		# Name of executable

# Specify that target files should be kept in a distinct directory from the sources.
VariantDir(build, src, duplicate=0)

# Create environment
env = Environment()

# Specify external libs to be linked
#env.AppendUnique(LIBS=BOOST_LIBS) # Specifies libraries 
#env.AppendUnique(LIBPATH=BOOST_LIBS_PATH)

# Specify the location of header files in C preprocessor path
env.AppendUnique(CPPPATH=include)


# Make the C++ compiler use the C++11/14 standard, enable debug info, and so on.
env.AppendUnique(CXXFLAGS=['-std=c++14', '-g', '-Wall', '-pedantic', '-Wno-long-long', '-O3', '-static'])

# Build program (source directory is changed to build to allow distinct .cpp and .o locations)
program = env.Program(target = bin + '/' + program, source = Glob(build + '/*.cpp'))

# Run
output = env.Command('run', [], './bin/trees')

# Run with valgring
#output = env.Command('runValgring', [], 'valgrind -q --leak-check=full --track-origins=yes ./bin/trees')
#output = env.Command('runValgring', [], 'valgrind -q --leak-check=full ./bin/trees')

# Run with valgring for profiling
#output = env.Command('runValgring', [], 'valgrind -q --tool=callgrind ./bin/trees')

#env.AlwaysBuild(program)
env.AlwaysBuild(output)

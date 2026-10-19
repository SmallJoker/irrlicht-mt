set(IRREXAMPLES
	# removed
)
if(UNIX)
	list(APPEND IRREXAMPLES AutomatedTest)
endif()

foreach(exname IN ITEMS ${IRREXAMPLES})
	file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/${exname}/*.cpp")
	add_executable(${exname} ${sources})

	if(NOT MSVC)
		string(APPEND CMAKE_CXX_FLAGS " -Wall -g")
	endif()

	target_include_directories(${exname} PRIVATE
		${CMAKE_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/${exname}
	)
	target_link_libraries(${exname} IrrlichtMt)
endforeach()

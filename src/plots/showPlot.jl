include(joinpath(".", "..", "..", "inc", "plots","showPlots_utils.jl"))

function main()
    # Check the arguments and get the absolute path
    absolute_path = CheckArgument(ARGS)
    # Read the JSON file
    graph = ReadJSON(absolute_path)
    # Get the filename without extension
    filename, ext = splitext(basename(absolute_path))
    # Plot the graph
    PlotGraph(graph, basename(filename))
    # Ask the user if he wants to resolve the Hamiltonian Cycle problem
    resolver(graph, filename)
    
    println(green("End of the program, the plots are in the 'img' folder."))
    
    sleep(5)
end

main()
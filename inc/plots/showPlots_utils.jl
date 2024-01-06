import Pkg

println("Adding packages...\n")
using  Graphs, GraphPlot, Colors, JSON, Compose, Cairo, JuMP, GLPK

# Colors for the terminal
green(text) = "\033[32m$text\033[0m"
error(text) = "\033[31m$text\033[0m"


"""
ReadJSON(filename)
Reads a JSON file and constructs an adjacency list matrix based on the data.
* Arguments
- `filename`: The path to the JSON file.
* Returns
- `adj_list`: The adjacency list matrix.
"""
function ReadJSON(filename)
    println("Reading JSON file: ", filename , "\n")
    # Read the JSON file
    data = JSON.parsefile(filename)
    matrix_adjacency = data["adjacencies"]
    # Determine the size of the adjacency matrix
    n = length(matrix_adjacency)
    # Initialize the adjacency list matrix with empty lists
    adj_list = zeros(Int64, n, n)
    # Construct the adjacency list
    for (key, value) in matrix_adjacency
        i = parse(Int64, key) + 1  # Convert string key to integer and adjust for 1-based indexing
        for j in value
            adj_list[i, j + 1] = 1  # Adjust j for 1-based indexing
        end
    end

    return adj_list
end



"""
PlotGraph(adj_matrix, filename)
Save a image of a plot of a graph based on an adjacency matrix.
* Arguments
- `adj_matrix`: The adjacency matrix representing the graph.
- `filename`: The name of the file to save the plot.

* The image will be saved in the 'img' folder.
"""
function PlotGraph(adj_matrix, filename)
    println("Plotting the graph\n")
    EPS = 0.00001
    N = size(adj_matrix)[1]
    G = Graphs.SimpleGraph(N)
    # Add the edges to the graph
    for i=1:N, j=1:N
        if adj_matrix[i,j] > EPS
            Graphs.add_edge!(G,i,j)
        end
    end
    pastel_green = RGB(0.6, 0.8, 0.5)

   # Determinar el tamaño de la cuadrícula
   locs_y = Float64[0 for i=1:N]
   locs_x = Float64[0 for i=1:N]

    # Generar coordenadas en una cuadrícula 
    k = 0
    m = 0
    for i in 1:2:(N-1)
        i = Int(i)
        for j in 1:2
            locs_x[i] = j + k
            locs_x[i+1] = j + 1 + k
        end
        locs_y[i] = m
        locs_y[i+1] = m
        m = m + 1
        if (i+1) % 12 == 0
            m = 0
            k = k + 2
        end
    end

    selectors = N % 12
    j = 0
    for i in (N-selectors+1):N
        locs_x[i] = (k / 2) + j
        locs_y[i] = 11
        j = j + 1
    end

    # Generate the plot
    p = gplot(G, nodelabel = 1:N, locs_x, locs_y, nodefillc = pastel_green, NODELABELSIZE = 3)
    # Create the path to save the plot
    path = joinpath(".", "img", filename * ".png")
    # Save the plot
    draw(PNG(path, 6inch, 4inch), p)
    println(green("Saved image in " * path * "\n"))
end



"""
PlotGraphSolution(adj_matrix, sol, filename)
Plot and save a graph plot with a given solution.
* Arguments
- `sol`: The solution matrix indicating the selected edges.
- `filename`: The name of the file to save the plot.

* The image will be saved in the 'img' folder.
"""
function PlotGraphSolution(sol, filename)
    println("Plotting the solution\n")
    EPS = 0.00001
    N = size(sol)[1]
    G = Graphs.SimpleDiGraph(N)
    # Adding edges to the graph
    for i=1:N, j=1:N
        if sol[i,j] > EPS
            Graphs.add_edge!(G, i, j)
        end
    end
    pastel_green = RGB(0.6, 0.8, 0.5)
    red = RGB(0.8, 0.4, 0.4)

    locs_y = Float64[0 for i=1:N]
    locs_x = Float64[0 for i=1:N]

    # Generar coordenadas en una cuadrícula y convertirlas a Float64
    k = 0
    m = 0
    for i in 1:2:(N-1)
        i = Int(i)
        for j in 1:2
            locs_x[i] = j + k
            locs_x[i+1] = j + 1 + k
        end
        locs_y[i] = m
        locs_y[i+1] = m
        m = m + 1
        if (i+1) % 12 == 0
            m = 0
            k = k + 2
        end
    end

    selectors = N % 12
    j = 0
    for i in (N-selectors+1):N
        locs_x[i] = (k / 2) + j
        locs_y[i] = 11
        j = j + 1
    end

    # Generate the plot
    p = gplot(G, nodelabel=1:N, locs_x, locs_y, nodefillc=pastel_green, edgestrokec = red, NODELABELSIZE = 3)
    # Create the path to save the plot
    path = joinpath(".", "img", filename * "_solution.png")
    # Save the plot
    draw(PNG(path, 6inch, 4inch), p)
    println(green("Saved image in " * path * "\n"))
end


    
"""
SolveHamilton(N, adj_list)
Solves the Hamiltonian Cycle problem.
* Arguments
- `adj_list`: The adjacency list representation of the graph.
* Returns
An array representing the solution to the Hamiltonian Cycle problem.

"""
function SolveHamilton(adj_list)
    println("Solving the Hamiltonian Cycle problem...\n")
    N = size(adj_list)[1]
    EPS = 0.00001
    model = Model(GLPK.Optimizer)
    set_silent(model)

    # Variables
    @variable(model, x[1:N,1:N], Bin)

    for i in 1:N
        set_upper_bound(x[i,i], 0)
    end

    for i in 1:N, j in 1:N
        if adj_list[i,j] < EPS
            set_upper_bound(x[i,j], 0)
        end
    end

    @objective(model, Min, 0)

    # Normal TSP constraints
    @constraint(model, [i=2:N], sum(x[i,:]) == 1)
    @constraint(model, [i=2:N], sum(x[:,i]) == 1)
    
    # Dinamic constraints
    while true
        optimize!(model)
        xval = JuMP.value.(x)
        G = Graphs.SimpleDiGraph(Graphs.Edge.([ (i,j) for i=1:N,j=1:N if xval[i,j]>0.5 ]) )
        Components = Graphs.connected_components(G)
        if length(Components)==1
            break
        end
        @constraint(model, [S in Components], sum(x[S,S]) <= length(S)-1 )
    end

    if termination_status(model) == OPTIMAL
        println("Hamiltonian Cycle problem solved!\n")
        return value.(x)
    else
        println("The problem is Infeasible, The number of selectors was too low\n")
        return -1
    end
    
  end



"""
CheckArgument(args)
Check if the command line argument is provided and if the specified file exists.
* Arguments
- `args::Array{String}`: Command line arguments.
* Returns
- `absolute_path::String`: The absolute path of the specified file.
"""
function CheckArgument(args)
    if length(args) < 1
        println("Use: julia showPlot.jl pathJSONFile")
        exit(1)
    end
    path = args[1]
    # Convert to absolute path
    absolute_path = abspath(path)
    # Check if the file exists
    if !isfile(absolute_path)
        println("The specified file does not exist: ", absolute_path)
        exit(1)
    end
    return absolute_path
end


"""
resolver(graph)
Ask the user if he wants to resolve the Hamiltonian Cycle problem.
* Arguments
- `graph`: The adjacency list representation of the graph.
"""
function resolver(graph, filename)
    print("Do you want to resolve the Hamiltonian Cycle problem? (y/n) :> ")
    while true
        resolve = readline()
        if resolve == "y"
            # Solve the Hamiltonian Cycle problem
            try
                x = SolveHamilton(graph)
                # Plot the solution
                PlotGraphSolution(x, basename(filename))
            catch
                println(error("The problem is Infeasible, The number of selectors was too low\n"))
                break
            end
            break
        elseif resolve == "n"
            break
        else
            println("Please, enter 'y' or 'n' :> ")
        end
    end
end

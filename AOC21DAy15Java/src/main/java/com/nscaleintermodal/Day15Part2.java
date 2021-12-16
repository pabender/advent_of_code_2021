package com.nscaleintermodal;

import org.jgrapht.Graph;
import org.jgrapht.alg.shortestpath.DijkstraShortestPath;
import org.jgrapht.graph.DefaultWeightedEdge;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Day15Part2 {

    private Graph<node,DefaultWeightedEdge> graph;

    private node startingPoint;
    private node endingPoint;

    public Day15Part2(String fileName){
        graph = new SimpleGraph(DefaultWeightedEdge.class);

        List<String> lines;

        File f =  new File(fileName);
        try {
            BufferedReader reader = new BufferedReader(new FileReader(f));
            lines = reader.lines().collect(Collectors.toList());
        } catch(java.io.FileNotFoundException fnfe) {
            lines = new ArrayList<>();
        }

        startingPoint = new node(0,0);
        endingPoint = new node(5*lines.get(0).length()-1,5*lines.size()-1);

        for(int i=0;i<5;i++) { //repeat up and down 5 times
            for (int j = 0; j < 5; j++) { // repeat to the side 5 times
                for (int y = 0; y < lines.size(); y++) {
                    for (int x = 0; x < lines.get(y).length(); x++) {
                        String w = lines.get(y).substring(x, x + 1);
                        node a = new node(x+j*lines.get(x).length(), y+i*lines.size());
                        if (!graph.containsVertex(a))
                            graph.addVertex(a);
                        node b = new node(x +j*lines.get(x).length() + 1, y+i*lines.size());
                        if (!graph.containsVertex(b))
                            graph.addVertex(b);
                        graph.setEdgeWeight(graph.addEdge(b, a), getWeight(w,lines.size(),lines.get(i).length(),j,i));
                        node c = new node(x+j*lines.get(x).length(), y +i*lines.size()+ 1);
                        if (!graph.containsVertex(c))
                            graph.addVertex(c);
                        graph.setEdgeWeight(graph.addEdge(c, a), getWeight(w,lines.size(),lines.get(i).length(),j,i));
                        node d = new node(x +j*lines.get(x).length()- 1, y+i*lines.size());
                        if (!graph.containsVertex(d))
                            graph.addVertex(d);
                        graph.setEdgeWeight(graph.addEdge(d, a), getWeight(w,lines.size(),lines.get(i).length(),j,i));
                        node e = new node(x+j*lines.get(x).length(), y +i*lines.size()- 1);
                        if (!graph.containsVertex(e))
                            graph.addVertex(e);
                        graph.setEdgeWeight(graph.addEdge(e, a), getWeight(w,lines.size(),lines.get(i).length(),j,i));
                    }
                }
            }
        }

    }

    private Integer getWeight(String w,int lines, int columns, int xrepeat,int yrepeat) {
        int retval = Integer.valueOf(w);
        for(int i=0;i<xrepeat+yrepeat;i++) {
            retval++;
            if(retval==10)
                retval=1;
        }

        return retval;
    }

    int nodeCount(){
        return graph.vertexSet().size();
    }


    public double getPathWeight() {
        DijkstraShortestPath<node, DefaultWeightedEdge> dijkstra = new DijkstraShortestPath<node, DefaultWeightedEdge>(graph);
        System.out.println(dijkstra.getPath(startingPoint,endingPoint).toString());
        return dijkstra.getPathWeight(startingPoint, endingPoint);
    }
}

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

public class Day15Part1 {

    private Graph<node,DefaultWeightedEdge> graph;

    private node startingPoint;
    private node endingPoint;

    public Day15Part1(String fileName){
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
        endingPoint = new node(lines.get(0).length()-1,lines.size()-1);

        for(int y=0;y<lines.size();y++) {
           for(int x=0;x<lines.get(y).length();x++) {
               String w = lines.get(y).substring(x,x+1);
               node a = new node(x,y);
               if(!graph.containsVertex(a))
                   graph.addVertex(a);
               node b = new node(x+1,y);
               if(!graph.containsVertex(b))
                   graph.addVertex(b);
               graph.setEdgeWeight(graph.addEdge(b,a),Integer.valueOf(w));
               node c = new node(x,y+1);
               if(!graph.containsVertex(c))
                   graph.addVertex(c);
               graph.setEdgeWeight(graph.addEdge(c,a),Integer.valueOf(w));
               node d = new node(x-1,y);
               if(!graph.containsVertex(d))
                   graph.addVertex(d);
               graph.setEdgeWeight(graph.addEdge(d,a),Integer.valueOf(w));
               node e = new node(x,y-1);
               if(!graph.containsVertex(e))
                   graph.addVertex(e);
               graph.setEdgeWeight(graph.addEdge(e,a),Integer.valueOf(w));
           }
        }

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

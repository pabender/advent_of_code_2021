package com.nscaleintermodal;

import org.jgrapht.graph.DefaultDirectedWeightedGraph;
import org.jgrapht.graph.DefaultWeightedEdge;

public class SimpleGraph extends DefaultDirectedWeightedGraph<node, DefaultWeightedEdge> {

    public SimpleGraph(Class<? extends DefaultWeightedEdge> edgeClass) {
        super(edgeClass);
    }

}

package com.nscaleintermodal;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day15Part2Tests {

    @Test
    public void graphInitialized(){
        String dataFileName = this.getClass().getResource("testdata.txt").getFile();
        Day15Part2 testObject = new Day15Part2(dataFileName);
        assertThat(testObject.nodeCount()).isEqualTo(2700);
    }

    @Test
    public void pathWeightCorrectForSample(){
        String dataFileName = this.getClass().getResource("testdata.txt").getFile();
        Day15Part2 testObject = new Day15Part2(dataFileName);
        double weight = testObject.getPathWeight();
        assertThat(weight).isEqualTo(315);
    }

    @Test
    public void pathWeightCorrectForInput(){
        String dataFileName = this.getClass().getResource("input.txt").getFile();
        Day15Part2 testObject = new Day15Part2(dataFileName);
        double weight = testObject.getPathWeight();
        assertThat(weight).isEqualTo(2952);
    }

}

package com.nscaleintermodal;

import org.junit.jupiter.api.Test;

import java.io.File;

import static org.assertj.core.api.Assertions.assertThat;

public class Day15Part1Tests {

    @Test
    public void graphInitialized(){
        String dataFileName = this.getClass().getResource("testdata.txt").getFile();
        Day15Part1 testObject = new Day15Part1(dataFileName);
        assertThat(testObject.nodeCount()).isEqualTo(140);
    }

    @Test
    public void pathWeightCorrectForSample(){
        String dataFileName = this.getClass().getResource("testdata.txt").getFile();
        Day15Part1 testObject = new Day15Part1(dataFileName);
        double weight = testObject.getPathWeight();
        assertThat(weight).isEqualTo(40);
    }

    @Test
    public void pathWeightCorrectForSmallSampleFromReddit(){
        String dataFileName = this.getClass().getResource("smalltest.txt").getFile();
        Day15Part1 testObject = new Day15Part1(dataFileName);
        double weight = testObject.getPathWeight();
        assertThat(weight).isEqualTo(8);
    }

    @Test
    public void pathWeightCorrectForInput(){
        String dataFileName = this.getClass().getResource("input.txt").getFile();
        Day15Part1 testObject = new Day15Part1(dataFileName);
        double weight = testObject.getPathWeight();
        assertThat(weight).isEqualTo(696);
    }

}

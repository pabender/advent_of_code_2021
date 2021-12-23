package com.nscaleintermodal;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day22Part1Tests {
    @Test
    public void countCountCorrectForSample(){
        String dataFileName = this.getClass().getResource("testdata.txt").getFile();
        Day22Part1 testObject = new Day22Part1(dataFileName);
        double count = testObject.getPathCount();
        assertThat(count).isEqualTo(39);
    }

    @Test
    public void countCorrectForLargerTestSample(){
        String dataFileName = this.getClass().getResource("largertestdata.txt").getFile();
        Day22Part1 testObject = new Day22Part1(dataFileName);
        double count = testObject.getPathCount();
        assertThat(count).isEqualTo(590784);
    }

    @Test
    public void countCorrectForPart2LargerTestSample(){
        String dataFileName = this.getClass().getResource("largertestdata2.txt").getFile();
        Day22Part1 testObject = new Day22Part1(dataFileName);
        double count = testObject.getPathCount();
        assertThat(count).isEqualTo(474140);
    }

    @Test
    public void countCountCorrectForInput(){
        String dataFileName = this.getClass().getResource("input.txt").getFile();
        Day22Part1 testObject = new Day22Part1(dataFileName);
        double count = testObject.getPathCount();
        assertThat(count).isEqualTo(591365);
    }
}

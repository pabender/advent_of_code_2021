package com.nscaleintermodal;
import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class Day22Part2Tests {
    @Test
    public void countCountCorrectForSample(){
        String dataFileName = this.getClass().getResource("testdata.txt").getFile();
        Day22Part2 testObject = new Day22Part2(dataFileName);
        double count = testObject.getCount();
        assertThat(count).isEqualTo(39);
    }

    @Test
    public void countCorrectForLargerTestSample(){
        String dataFileName = this.getClass().getResource("largertestdata.txt").getFile();
        Day22Part2 testObject = new Day22Part2(dataFileName);
        double count = testObject.getCount();
        assertThat(count).isEqualTo(590784);
    }

    @Test
    public void countCorrectForPart2LargerTestSample(){
        String dataFileName = this.getClass().getResource("largertestdata2.txt").getFile();
        Day22Part2 testObject = new Day22Part2(dataFileName);
        double count = testObject.getCount();
        assertThat(count).isEqualTo(2758514936282235d);
    }

    @Test
    public void countCountCorrectForInput(){
        String dataFileName = this.getClass().getResource("input.txt").getFile();
        Day22Part2 testObject = new Day22Part2(dataFileName);
        double count = testObject.getCount();
        assertThat(count).isEqualTo(591365);
    }
}

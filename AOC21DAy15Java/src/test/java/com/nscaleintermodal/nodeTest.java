package com.nscaleintermodal;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.as;
import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.*;

class nodeTest {

    @Test
    void getX() {
        assertThat(new node(1,2).getX()).isEqualTo(1);
    }

    @Test
    void getY() {
        assertThat(new node(1,2).getY()).isEqualTo(2);
    }

    @Test
    void testEqualsAndHashCode() {
        node a = new node(1,2);
        node b = new node(1,2);
        node c = new node(2,2);

        assertThat(a).isEqualTo(b)
                .isNotEqualTo(c)
                .hasSameHashCodeAs(b)
                .doesNotHaveSameHashCodeAs(c);
    }

}
package simplemath

import "testing"

func TestSqrt1(t *testing.T) {
    v := Sqrt(16)
    if v != 4 {
        t.Errorf("Sqrt(4) failed. Got %d, expected 4.", v)
    }
}

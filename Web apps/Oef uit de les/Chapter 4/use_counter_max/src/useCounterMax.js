import { useState } from "react";

function useCounterMax(max) {
    const [value, setValue] = useState(0);

    function incr() {
        if (value < max) setValue(value + 1);

    }
    function decr() {
        setValue(value - 1);
    }

    let error = "";
    if (value >= max) error = `Message: the maximum (${max}) is reached`;
    return [value, incr, decr, error];
}

export default useCounterMax;
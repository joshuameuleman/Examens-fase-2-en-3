import { useState, useEffect } from "react";

function Counter() {
    const [value, setValue] = useState(0);

    function incrValue() {
        // 1)
        setValue(value + 1);

        // 2)
        //setValue(value + 1); // The value of "value" is modified,
        //setValue(value + 1); // but here we are using the old value of "value"
        // (not the one that has just been incremented).

        // 3)
        //setValue(function (value) { return value + 1 }); // "value" is updated,
        //setValue((value) => value + 1 ); // then we use its new value.

        // 4) en 5)
        //setValue(function (value) { return value + 1 });
    }

    // 4)
    //setValue(1);

    // 5)
    /*
    useEffect(function () {
        setValue(1);
    }, []); // conditions = [] means that setValue(1) is executed only on the initial display.
    */

    return (
        <>
            <button onClick={incrValue}>value + 1</button>
            &nbsp;=&gt;
            value = {value};
            &nbsp;&nbsp;
        </>
    )
}

export default Counter;
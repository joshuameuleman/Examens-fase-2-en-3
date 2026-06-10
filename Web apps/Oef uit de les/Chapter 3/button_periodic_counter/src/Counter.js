import { useState, useEffect } from "react";

function Counter(props) {
    const init = parseInt(props.init || 0);
    const end = parseInt(props.end || 0);
    const [count, setCount] = useState(init);
    const [start, setStart] = useState(true); // true for displaying the Start button
    let timer; // toegevoegd

    useEffect(function () {
        if (!start) {
            // The Start button is not displayed; you can initiate the timer.
            // "var" verwijderd
            timer = setInterval(function () {
                setCount((count) => {
                    const newCount = count + 1; // "var" => "const"
                    if (newCount >= end) setStart(true);
                    return newCount;
                });
            }, 1000);
        }

        return function () {
            clearInterval(timer);
        }
    });

    function restart() {
        setStart(false); // Hide the Start button
        setCount(init); // Reset "count" to the initial value.
    }

    return (
        <>
            Initial value of the counter is: {init}
            <br />
            End of the counter at: {end}
            <br />
            The counter is: {count}
            <br />
            {
                (start) ?
                    <>
                        <b>Counter stopped</b>&nbsp;
                        <button onClick={restart}>Start</button>
                    </> :
                    <i>Counter in progress</i>
            }
        </>
    )
}

export default Counter;
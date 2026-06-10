import { useState, useEffect } from "react";

function Counter(props) {
    const init = parseInt(props.init || 0);
    const end = parseInt(props.end || 0);
    const [count, setCount] = useState(init);

    function incr() {
        setCount((count) => count + 1);
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
                (count < end) ?
                    <>
                        <i>Counter in progress</i>&nbsp;
                        <button onClick={incr}>count+1</button>
                    </> :
                    <b>Counter stopped</b>
            }
        </>
    )
}

export default Counter;
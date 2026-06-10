import { useState, useEffect } from "react";

function useForceUpdate() {
    const [value, setBoolean] = useState(true);

    function forceUpdate() {
        setBoolean(!value); // Invert the value of the reactive variable
    }

    return forceUpdate;
}

export default useForceUpdate;
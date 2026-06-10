import { useRef } from "react";

function usePreviousState(state) {
    const ref = useRef();
    const oldValue = ref.current;
    ref.current = state;

    return oldValue;
}

export default usePreviousState;
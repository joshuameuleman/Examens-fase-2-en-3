import useFetch from "./useFetch";

function Countries() {
    const [data, error] = useFetch("https://restcountries.com/v3.1/all?fields=name");
    // andere velden, zie op https://restcountries.com/#fields-mandatory

    return (
        <>
            {(!error && !data) ? <>Waiting</> :
                (error ? <>{error}</> : <>{data}</>)
            }
        </>
    )
}

export default Countries;
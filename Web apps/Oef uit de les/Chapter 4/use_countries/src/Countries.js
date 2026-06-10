import useCountries from "./useCountries";
import { Fragment } from "react";

function Countries() {
    const countries = useCountries();

    return (
        <>
            {(!countries) ? <>Waiting</> :
                (
                    <>{
                        countries.map(function (name, index) {
                            return <Fragment key={index}>{name}
                            <br />
                            </Fragment>
                        })
                    }</>
                )
            }
        </>
    )
}

export default Countries;
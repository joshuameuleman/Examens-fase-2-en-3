import useCountries from "./useCountries";
import { Fragment } from "react";

function Countries({name}) {
    const countries = useCountries(name);

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
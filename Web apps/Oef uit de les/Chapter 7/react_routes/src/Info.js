import { useSearchParams, useParams } from "react-router-dom";

function Info() {
  //use of HTTP query:
  //const [searchParams, setSearchParams] = useSearchParams();
  //const firstname = searchParams.get("firstname");

  //use of URL parameter:
  const { firstname } = useParams();

  return <h1>Hello, {firstname}!</h1>;
}

export default Info;
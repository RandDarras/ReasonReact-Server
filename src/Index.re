/* to require the external files that will be used */

[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ExampleStyles.style;

/*  for styling >> DOM Manuplation  */
let makeContainer = text => {
  let container = document##createElement("div");
  container##className #= "container";

  let title = document##createElement("div");
  title##className #= "containerTitle";
  title##innerText #= text;

  let content = document##createElement("div");
  content##className #= "containerContent";

  let () = container##appendChild(title);
  let () = container##appendChild(content);
  let () = document##body##appendChild(container);

  content;
};

/* building component with the using of pattern matching and Reason react life sycle to build the routers */ 
[@react.component]

let component = ReasonReact.reducerComponent();

let make = _children => {
  ...component,

  didMount: self => {
 
    let url = ReasonReactRouter.useUrl();
    let watcherID =
   ReasonReact.Router.watchUrl(url => {
     switch (url.path) {
     /*if path is hello >> render hello world withing "BlinkingGreeting" style */

     | ["hello"] => ReactDOMRe.render(
      <BlinkingGreeting> {React.string("Hello World!")} </BlinkingGreeting>,
      makeContainer("Blinking Greeting"),
    );
    /* if path is "hello" / any value >> render hello + {value} */
      | ["hello", param] => ReactDOMRe.render(
        <BlinkingGreeting> {React.string("Hello " ++ param )} </BlinkingGreeting>,
        makeContainer("Blinking Greeting"),
      );


     }
   });

    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },

}

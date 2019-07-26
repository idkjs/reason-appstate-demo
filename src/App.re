open ReactNative;
open Expo;

let styles =
  Style.(
    StyleSheet.create({
      "container":
        style(
          ~flex=1.,
          ~justifyContent=`center,
          ~alignItems=`center,
          ~backgroundColor="#F5FCFF",
          (),
        ),
      "instructions": style(~textAlign=`center, ~color="#ffffff", ()),
    })
  );
module Demo = {
  [@react.component]
  let make = () => {
    let (appState, setAppState) = React.useState(() => AppState.currentState);
    Js.log(appState);

    let handleAppStateChange = (nextAppState: AppState.t) => {
      Js.log2("nextAppState: ", nextAppState);
      Js.log2("appState: ", appState);
      switch (appState, nextAppState) {
      | (_background, _active) => Js.log("App has come to the foreground!")
      | (_inactive, _active) => Js.log("App has come to the foreground!")
      | _ => ()
      };
      setAppState(_ => nextAppState);
    };

    React.useEffect(() => {
      AppState.addEventListener(
        `change(state => handleAppStateChange(state)),
      )
      |> ignore;
      Some(
        () =>
          AppState.removeEventListener(
            `change(state => handleAppStateChange(state)),
          ),
      );
    });

    let renderAppState =
      switch (appState) {
      | _active => "active"
      | _background => "background"
      | _inactive => "inactive"
      };
    <Text> {"Current state is: " ++ renderAppState |> React.string} </Text>;
  };
};
[@react.component]
let app = () =>
  <View style=styles##container>
    <LinearGradient
      colors=[|"#DD4B39", "#C62C19"|]
      start=[|0.0, 0.0|]
      _end=[|1.0, 1.0|]
      style=Style.(style(~padding=dp(12.), ~borderRadius=12., ()))>
      <View style=styles##instructions>
        <Demo />
      </View>
    </LinearGradient>
  </View>;
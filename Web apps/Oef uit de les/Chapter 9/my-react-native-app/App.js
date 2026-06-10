import React from "react";
import Counter from "./Counter.js";
import { StatusBar } from "expo-status-bar";
import { View, StyleSheet, Platform, Button, Alert } from "react-native";
import Constants from "expo-constants";

function click() {
  Alert.alert("Hello");
}

export default function App() {
  return (
    <View style={styles.container}>
      <Counter />
      <Button onPress={click} title="Click me"></Button>
      <StatusBar style="auto" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: "flex-start",
    alignItems: "flex-start",
    backgroundColor: "#f5f5f5",
    marginTop: Platform.OS === "android" ? Constants.statusBarHeight : 50,
  },
});
# Notes extract: vives - ngrx - redux for angular.pdf

- Pages: 32
- Approx characters extracted: 7868
- Outline items: 33

## Outline (best effort)
- template slides
- Dia 1: NGRX Redux for Angular
- Dia 2
- Dia 3: ten industries
- Dia 4: global footprint of delaware office locations
- Dia 5
- Dia 6
- Dia 7: Starting your career at delaware?
- Dia 8: NGRX Redux for Angular
- Dia 9
- Dia 10
- Dia 11
- Dia 12
- Dia 13
- Dia 14: Redux principles
- Dia 15: Actions
- Dia 16: Creating actions
- Dia 17: Reducers
- Dia 18: Create a reducer function
- Dia 19: New way of creating a reducer function
- Dia 20: Reducers are pure functions
- Dia 21: Selectors
- Dia 22: Observables ?
- Dia 23: Do you have to put everything in the state ?
- Dia 24: Checklist: SHARI
- Dia 25: What Should Not Go in the Store?
- Dia 26
- Dia 27: Effects
- Dia 28: Sandboxes
- Dia 29
- Dia 30: Responsibilities of the sandbox
- Dia 31: NEXT TIME FOR ACTION
- Dia 32

## Per page

### Page 1: Paul Mestrum / 21.11.24
- Paul Mestrum / 21.11.24
- NGRX
- Redux for Angular

### Page 2: (no title detected)

### Page 3: ten industries
- ten industries
- we commit. we deliver.3
- manufacturing
- automotive
- pharma
- retail
- aerospace utilities food healthcare
- chemicals
- print & packaging

### Page 4: The Netherlands (Den Bosch, Naarden, Eindhoven)
- global delivery
- centres
- global footprint of
- delaware office
- locations
- 4,600 professionals
- 37 offices in
- 19 countries
- €490 mil
- revenue
- global delivery network
- 2019 – 2022

### Page 5: KORTRIJK
- KORTRIJK
- ANTWERP
- GENT
- LUMMEN
- WAVRE
- DELAWARE BELGIUM LUIK

### Page 6: › Dot NET core – C#
- Frontend development
- Angular
- React
- T echnologies
- Ionic & cordova
- PWA
- Projects
- Web applications
- xADP: mobile,
- IoT
- Chats / assistants

### Page 7: Isabel Bergsma Isabel.bergsma@delaware.pro
- Starting your career at delaware?
- …or get in touch with one of our junior recruiter
- Isabel Bergsma Isabel.bergsma@delaware.pro
- Check out our career website…

### Page 8: Paul Mestrum / 08.11.23
- Paul Mestrum / 08.11.23
- NGRX
- Redux for Angular

### Page 9: App Component
- change name
- App Component
- Other Component Other Component
- Main ComponentUser Component
- inform parent

### Page 10: View / App
- View / App
- ReducersAction
- dispatch
- create new
- state
- pass state with
- subscriptions
- Store
- Store in
- store

### Page 11: View / App
- View / App
- Reducers
- Store
- Action
- dispatch
- create new
- state
- pass state with
- subscriptions
- Action:
- type: ‘CHANGE_NAME’
- payload ‘Piet’

### Page 12: App Component
- App Component
- Main ComponentUser Component
- Other Component Other Component
- dispatch
- action
- pass state
- Store reduce state

### Page 13: 13

### Page 14: Redux principles
- Single source of truth, called “The Store”
- State is read-only and can only be changed by dispatching
- Changes are made using pure functions called reducers

### Page 15: Actions
- Action = object with type and payload:
- Examples:
- Adding items in the cart
- Storing UI settings (eg active tab/page => breadcrumbs, activated tab,

### Page 16: Creating actions
- Using a class:
- Using a create function:

### Page 17: Reducers
- Reducers
- Reducer = function that manipulate the state based on incoming actions
- function reducer(state, action): state;

### Page 18: Create a reducer function
- Create a reducer function
- function reducer(state: State = INITIAL_STATE, action: Actions):
- State {
- switch (action.type) {
- case ‘LOAD_USER’:
- return {
- ...state,
- users: [...state.users, action.payload]
- return state;
- Reducers

### Page 19: New way of creating a reducer function
- New way of creating a reducer function
- const reducer = createReducer(INITIAL_STATE,
- on(loadUserAction, (state, payload) => ({
- ...state,
- users: [...state.users, action.payload]
- });
- Reducers

### Page 20: Reducers are pure functions
- A pure function is a function which:
- Given the same input, will always return the same output.
- Produces no side effects.

### Page 21: Selectors
- An observable that selects and maps the state

### Page 22: Observables ?
- An RxJS Observable is a data stream that can emit multiple values over time,

### Page 23: Do you have to put everything in the state ?
- Do you have to put everything in the state ?

### Page 24: Checklist: SHARI
- Checklist: SHARI
- Shared between many components and services
- Hydrated (persisted) from (local/session/?)storage
- Available when re-entering routes
- Retrieved with a side effect
- Impacted by actions from other sources
- https://www.youtube.com/watch?v=t3jx0EC-Y3c&ab_channel=ng-conf

### Page 25: What Should Not Go in the Store?
- Unshared state
- Angular form state
- Non serializable state

### Page 26: View / App
- View / App
- ReducersAction
- dispatch
- Store
- create new
- state
- pass state with
- subscriptions
- Effect Async service
- call async
- process
- Action

### Page 27: Effects
- Hard to debug
- Every action must be mapped to exactly 1 other action
- Your algorithm is spread in your code

### Page 28: Sandboxes
- (Brecht Billet)
- https://blog.strongbrew.io/A-scalable-angular2-architecture/
- https://blog.strongbrew.io/A-scalable-angular-architecture-part2/

### Page 29: Smart
- Smart
- component
- Sandbox
- ReducersAction
- dispatch
- Store
- create new
- state
- pass state with
- subscriptionsAsync service
- call async
- process

### Page 30: Responsibilities of the sandbox
- Sole interface for a smart component (container) to the
- Only exposes what this container needs
- 1 sandbox for 1 container
- Exposes
- State using selectors
- Actions using functions
- Routing to other pages using functions

### Page 31: NEXT
- NEXT
- TIME FOR ACTION
- GIT Repo:
- https://github.com/pmestrum/angular-ngrx-excercise/tree/v18/start
- https://bit.ly/4eBKKm9

### Page 32: 32 we commit. we deliver.
- 32 we commit. we deliver.

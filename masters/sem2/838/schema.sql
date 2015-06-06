create table user_data(
  user_id serial primary key,
  user_name varchar(100),
  category int
);

create table user_selection(
  user_id integer references user_data(user_id),
  color   real,
  shape   real,
  choice  int,
  priming int
);

grant all on user_data to "www-user";
grant all on user_selection to "www-user";

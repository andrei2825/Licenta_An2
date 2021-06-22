package fourth;

public class Song {
    private String name;
    private int id;
    private String composer;
    public Song(String name, int id, String composer) {
        this.name = name;
        this.id = id;
        this.composer = composer;
    }

    public String getName() {
        return name;
    }

    public int getId() {
        return id;
    }

    public String getComposer() {
        return composer;
    }

    @Override
    public String toString() {
        return "Song{" +
                "name='" + name + '\'' +
                ", id=" + id +
                ", composer='" + composer + '\'' +
                '}';
    }
}

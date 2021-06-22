package fourth;

public class ThrillerAlbum extends Album{

    public ThrillerAlbum(){}
    public void addSong(Song song) {
        String name = song.getName();
        int id = song.getId();
        String temp = "Michael Jackson";
        //Nu reusesc sa inteleg de ce nu adauga sia cest cantec(Thrilled) in album.
        if (name.equals(temp) && id % 2 == 0) {
            songs.add(song);
        }

    }
}
